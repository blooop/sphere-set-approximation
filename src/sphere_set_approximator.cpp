#include "sphere_set_approximator.hpp"

void SphereSetApproximator::simplify(std::string input_file, std::string output_obj, int max_faces, double max_ratio, double max_cost, bool check_manifold) {
    Eigen::MatrixXd V, OV;
    Eigen::MatrixXi F, OF;
    Eigen::VectorXi J, I;
    igl::read_triangle_mesh(input_file, OV, OF);
    if (max_faces == 0x7fffffff) {
        max_faces = max_ratio * OF.rows() + 0.5;
    }
    else {
        if (max_ratio < 1)
            max_faces = std::max(max_faces, (int)(max_ratio * OF.rows() + 0.5));
    }

    auto MyDecimate = [&](
        const Eigen::MatrixXd& V,
        const Eigen::MatrixXi& F,
        const size_t max_m,
        const double max_cost,
        Eigen::MatrixXd& U,
        Eigen::MatrixXi& G,
        Eigen::VectorXi& J,
        Eigen::VectorXi& I) {
        // 原始面数
        const int orig_m = F.rows();
        // 跟踪面数
        int m = F.rows();
        typedef Eigen::MatrixXd DerivedV;
        typedef Eigen::MatrixXi DerivedF;
        DerivedV VO;
        DerivedF FO;
        igl::connect_boundary_to_infinity(V, F, VO, FO);
        // decimate 将无法在非边缘流形网格上正常工作。
        // 这包括边界上有非流形顶点的网格，因为这些顶点在连接到无穷远时会创建非流形边缘。
        if (!igl::is_edge_manifold(FO))
        {
            return false;
        }

        auto stopping_condition =
            [&](
                const Eigen::MatrixXd& V,
                const Eigen::MatrixXi& F,
                const Eigen::MatrixXi& E,
                const Eigen::VectorXi& EMAP,
                const Eigen::MatrixXi& EF,
                const Eigen::MatrixXi& EI,
                const std::set<std::pair<double, int> >& Q,
                const std::vector<std::set<std::pair<double, int> >::iterator >& QIT,
                const Eigen::MatrixXd& C,
                const int e,
                const int e1,
                const int e2,
                const int f1,
                const int f2)->bool

        {
            // 仅当我们折叠真实面时才减去
            if (f1 < orig_m) m -= 1;
            if (f2 < orig_m) m -= 1;
            return (m <= (int)max_m) || (Q.begin()->first >= max_cost);
        };

        using namespace igl;

        Eigen::VectorXi EMAP;
        Eigen::MatrixXi E, EF, EI;
        edge_flaps(FO, E, EMAP, EF, EI);
        // 每个顶点的二次曲面
        typedef std::tuple<Eigen::MatrixXd, Eigen::RowVectorXd, double> Quadric;
        std::vector<Quadric> quadrics;
        per_vertex_point_to_plane_quadrics(VO, FO, EMAP, EF, EI, quadrics);
        // 状态变量跟踪我们刚刚折叠的边
        int v1 = -1;
        int v2 = -1;
        // 用于计算和更新度量的回调
        std::function<void(
            const int e,
            const Eigen::MatrixXd&,
            const Eigen::MatrixXi&,
            const Eigen::MatrixXi&,
            const Eigen::VectorXi&,
            const Eigen::MatrixXi&,
            const Eigen::MatrixXi&,
            double&,
            Eigen::RowVectorXd&)> cost_and_placement;
        std::function<bool(
            const Eigen::MatrixXd&                                         ,/*V*/
            const Eigen::MatrixXi&                                         ,/*F*/

            const Eigen::MatrixXi&                                         ,/*E*/
            const Eigen::VectorXi&                                         ,/*EMAP*/

            const Eigen::MatrixXi&                                         ,/*EF*/
            const Eigen::MatrixXi&                                         ,/*EI*/

            const std::set<std::pair<double, int> >&                        ,/*Q*/
            const std::vector<std::set<std::pair<double, int> >::iterator >&,/*Qit*/
            const Eigen::MatrixXd&                                         ,/*C*/
            const int                                                       /*e*/
        )> pre_collapse;
        std::function<void(
            const Eigen::MatrixXd&                                         ,   /*V*/
            const Eigen::MatrixXi&                                         ,   /*F*/
            const Eigen::MatrixXi&                                         ,   /*E*/
            const Eigen::VectorXi&                                         ,/*EMAP*/
            const Eigen::MatrixXi&                                         ,  /*EF*/
            const Eigen::MatrixXi&                                         ,  /*EI*/
            const std::set<std::pair<double, int> >&                        ,   /*Q*/
            const std::vector<std::set<std::pair<double, int> >::iterator >&, /*Qit*/
            const Eigen::MatrixXd&                                         ,   /*C*/
            const int                                                       ,   /*e*/
            const int                                                       ,  /*e1*/
            const int                                                       ,  /*e2*/

            const int                                                       ,  /*f1*/
            const int                                                       ,  /*f2*/
            const bool                                                  /*collapsed*/
        )> post_collapse;
        qslim_optimal_collapse_edge_callbacks(
            E, quadrics, v1, v2, cost_and_placement, pre_collapse, post_collapse);
        // 调用贪婪抽取器
        bool ret = decimate(
            VO, FO,
            cost_and_placement,
            stopping_condition,
            pre_collapse,
            post_collapse,
            E, EMAP, EF, EI,
            U, G, J, I);
        // 删除虚假的边界面并清理
        const Eigen::Array<bool, Eigen::Dynamic, 1> keep = (J.array() < orig_m);
        igl::slice_mask(Eigen::MatrixXi(G), keep, 1, G);
        igl::slice_mask(Eigen::VectorXi(J), keep, 1, J);
        Eigen::VectorXi _1, I2;
        igl::remove_unreferenced(Eigen::MatrixXd(U), Eigen::MatrixXi(G), U, G, _1, I2);
        igl::slice(Eigen::VectorXi(I), I2, 1, I);

        return ret;
    };

    MyDecimate(OV, OF, max_faces, max_cost, V, F, J, I);
    if (check_manifold) {
        std::set<std::pair<int, int> > dedges;
        for (int i = 0; i < F.rows(); ++i) {
            for (int j = 0; j < 3; ++j) {
                int v1 = F(i, j);
                int v2 = F(i, (j + 1) % 3);
                auto key = std::make_pair(v1, v2);
                if (dedges.count(key)) {
                    printf("Non manifold!\n");
                }
                dedges.insert(key);
            }
        }
        printf("Output is a manifold!\n");
    }

    igl::write_triangle_mesh(output_obj, V, F);
}

void SphereSetApproximator::manifold(std::string input_file, std::string output_file, int resolution) {
    char* modifiableInFilename = new char[strlen(input_file.c_str()) + 1]; 
    strcpy(modifiableInFilename, input_file.c_str());
    Model_OBJ obj;
    obj.Load(modifiableInFilename);
    obj.Process_Manifold(resolution);
    char* modifiableOutFilename = new char[strlen(output_file.c_str()) + 1]; 
    strcpy(modifiableOutFilename, output_file.c_str());
    obj.SaveOBJ(modifiableOutFilename);
}

void SphereSetApproximator::manifold_simple(const std::string &input_file, const std::string &output_file, const sphere_set_approximator_params &params) {
    // 将 manifold 结果保存到临时文件
    std::stringstream ss;
    ss << time(0);
    std::string tmp_file = "tmp_" + ss.str() + ".obj";
    manifold(input_file, tmp_file, params.resolution);

    // simplify 处理
    simplify(tmp_file, output_file, params.max_faces, params.max_ratio, params.max_cost, params.check_manifold);

    // 删除临时文件
    remove(tmp_file.c_str());
}


bool SphereSetApproximator::approximate_spheres(const std::string &input_file, const std::string &pt_output_file, const sphere_set_approximator_params &params) {
    
    std::stringstream ss;
    ss << time(0);
    std::string tmp_file = "tmp_simplify_" + ss.str() + ".obj";
    manifold_simple(input_file, tmp_file, params);

    // load meshs
    RTcore::Mesh mesh = RTcore::objmesh(input_file.c_str());
    RTcore::Mesh manifold = RTcore::objmesh(tmp_file.c_str());
    std::string visualizer_mesh_filename = input_file;
    remove(tmp_file.c_str());
    // examine mesh orientation
    test_all_normal_outward(manifold);

    // sphere construction
    srand(params.seed);
    auto spheres = sphere_set_approximate(pt_output_file, mesh, visualizer_mesh_filename, manifold, params.n_sphere, params.n_innersample, params.n_surfacesample, params.n_finalsample, params.n_mutate);

    // output spheres
    for (auto s: spheres)
        std::cout << s.center << " " << s.radius << std::endl;

    // evaluate how well the spheres fit the model
    visualize(spheres, visualizer_mesh_filename);
    console.log("Evaluating...");
    console.info("Relative Outside Volume (Er):", volume(spheres, 10000000)/volume(manifold, 10000000)-1);

    return true;
}
