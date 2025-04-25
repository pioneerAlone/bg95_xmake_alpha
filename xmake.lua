-- Add build mode rules
add_rules("mode.debug", "mode.release")

-- Define variables
local framework_dir = "bg95/SDK1.1.12"
local entry_point = "0x40000000" -- Entry point address
local ld_script = path.join("bg95", "quectel_dam_demo.ld")
local build_dir = "bin"
local elf_name = "quectel_demo.elf"
local bin_name = "quectel_demo.bin"
local map_name = "quectel_demo.map"
local map_file = path.join(build_dir, map_name)
local lib_path = path.join(framework_dir, "lib") -- Directory for static libraries

-- Define toolchain paths
local toolchain_root = "C:/compile_tools/Snapdragon-llvm-4.0.3-windows64"
local toolchain_bin = path.join(toolchain_root, "bin")
local toolchain_standards = path.join(toolchain_root, "armv7m-none-eabi/libc/include")
local llvm_lib = path.join(toolchain_root, "lib/clang/4.0.3/lib")
local llvm_link_path = path.join(toolchain_root, "tools/bin")
local clangxx = path.join(toolchain_bin, "clang++")

-- Configure toolchain
toolchain("snapdragon-llvm")
    set_kind("standalone")
    set_sdkdir(toolchain_root) -- Set the root directory of the toolchain
    -- Set toolchain tools
    set_toolset("cc", "clang") -- C compiler
    set_toolset("cxx", "clang++") -- C++ compiler
    set_toolset("ld", "clang++") -- Linker
    set_toolset("ar", "llvm-ar") -- Static library tool
    set_toolset("strip", "llvm-strip") -- Symbol stripping tool
    set_toolset("as", "clang") -- Assembler

    -- Load toolchain configuration
    on_load(function (toolchain)
        -- Add compile options
        toolchain:add("cxflags",
            "-marm", "-target", "armv7m-none-musleabi", "-mfloat-abi=soft",
            "-mcpu=cortex-a7", "-mno-unaligned-access", "-fms-extensions",
            "-O0", "-g", "-fshort-enums", "-Wbuiltin-macro-redefined","-Wno-unused-value"
        )

        -- Add linker options
        toolchain:add("ldflags",
            "-v", "-d", "-target", "armv7m-none-musleabi", "-fuse-ld=qcld", "-lc++",
            "-Wl,-mno-unaligned-access", "-fuse-baremetal-sysroot", "-fno-use-baremetal-crt",
            "-Wl,-entry=" .. entry_point, "-Wl,-T" .. ld_script,
            "-Wl,-Map=" .. map_file .. ",-gc-sections", "-Wl,-gc-sections"
        )
        toolchain:add("includedirs", toolchain_standards, llvm_lib)
    end)

toolchain_end()

-- Define target
target("bg95_pika_alpha")
    set_kind("binary")
    set_filename(elf_name)
    set_toolchains("snapdragon-llvm")
    set_targetdir(build_dir)

    -- Add source files
    add_files(path.join(framework_dir, "*.S")) -- Add assembly files
    add_files("src/**.c")
    add_files(path.join(framework_dir, "quectel", "*.c"))

    -- Add include directories
    add_includedirs(
        path.join(framework_dir, "qapi"),
        path.join(framework_dir, "quectel"),
        path.join(framework_dir, "threadx_api")
    )
    --set_objectdir("build/objs")

    -- Add macro definitions
    add_defines(
        "QAPI_TXM_MODULE", "TXM_MODULE", "TX_DAM_QC_CUSTOMIZATIONS",
        "TX_ENABLE_PROFILING", "TX_ENABLE_EVENT_TRACE", "TX_DISABLE_NOTIFY_CALLBACKS",
        "FX_FILEX_PRESENT", "TX_ENABLE_IRQ_NESTING", "TX3_CHANGES"
    )

    

    -- Add linker options, directly specify the full path of .lib files
    add_ldflags(
        path.join(lib_path, "diag_dam_lib.lib"),
        path.join(lib_path, "qapi_psm_lib.lib"),
        path.join(lib_path, "timer_dam_lib.lib"),
        path.join(lib_path, "txm_lib.lib"),
        {force = true} -- Force the use of these options
    )

    -- Add post-build step: generate .bin file
    after_build(function (target)
        local elf_path = path.join(build_dir, elf_name)
        local bin_path = path.join(build_dir, bin_name)
        os.execv("py -2", {
            path.join(llvm_link_path, "llvm-elf-to-hex.py"),
            "--bin", elf_path,
            "--output", bin_path
        })
        print("Generated binary:", bin_path)
    end)