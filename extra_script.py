import os
Import("env")

# include toolchain paths
env.Replace(COMPILATIONDB_INCLUDE_TOOLCHAIN=True)

# override compilation DB path

env.Replace(COMPILATIONDB_PATH=os.path.join("$BUILD_DIR", "compile_commands.json"))

# global_env = DefaultEnvironment()

# for e in (env, global_env):
#     try:
#         print(e['CXXFLAGS'])
#         # key may or may not exist
#         e['CXXFLAGS'].remove("-std=gnu++11")
#     except:
        
#         pass
#     e['CXXFLAGS'].append("-std=gnu++17")v