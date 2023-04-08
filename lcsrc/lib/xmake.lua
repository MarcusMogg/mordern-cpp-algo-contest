xmaadd_requires("argparse","fmt","nlohmann_json","libcurl")

target("two-sum")
    set_kind("static")
    add_files("*.cc")
    add_headerfiles("*.h")