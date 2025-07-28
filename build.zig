const std = @import("std");

const windows_flags = [_][]const u8{
    "-DNONDLL",
    "-DBGDWIN32",
};

fn buildLibGd(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) *std.Build.Step.Compile {
    // get libgd source directory from build.zig.zon
    const gd_dep = b.dependency("libgd", .{});
    // get libpng and build it with the right target and optimization
    const png_dep = b.dependency("libpng", .{ .target = target, .optimize = optimize });
    const png_lib = png_dep.artifact("png");

    const gd_mod = b.createModule(.{
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });
    gd_mod.addCSourceFiles(.{
        .files = &.{
            "gd.c",
            "gd_color.c",
            "gd_color_match.c",
            "gd_io.c",
            "gd_io_dp.c",
            "gd_io_file.c",
            "gd_png.c",
            "gd_security.c",
            "gdhelpers.c",
            "gdtables.c",
        },
        .root = gd_dep.path("src"),
        .flags = &.{
            "-DHAVE_STDINT_H",
            "-DHAVE_INTTYPES_H",
            "-DHAVE_LIBPNG",
        },
    });
    if (target.result.os.tag == .windows) {
        for (windows_flags) |f| {
            gd_mod.addCMacro(f, "1");
        }
    }
    gd_mod.linkLibrary(png_lib);

    const gd_lib = b.addStaticLibrary(.{
        .root_module = gd_mod,
        .name = "gd",
    });

    // expose all header files in src in the include path for modules linking against libgd
    gd_lib.installHeadersDirectory(gd_dep.path("src"), "", .{});

    return gd_lib;
}

pub fn build(b: *std.Build) void {
    // collect target and optimization level from user's system or flags
    // (-Dtarget, -Dcpu, -Doptimize)
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe_mod = b.createModule(.{
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });
    exe_mod.addCSourceFiles(.{
        .files = &.{
            "src/color.c",
            "src/main.c",
            "src/mandelbrot.c",
            "src/text_handle.c",
        },
        .flags = if (target.result.os.tag == .windows)
            &windows_flags
        else
            &.{},
    });

    const gd_lib = buildLibGd(b, target, optimize);
    exe_mod.linkLibrary(gd_lib);

    const exe = b.addExecutable(.{
        .name = "cmandel",
        .root_module = exe_mod,
    });

    b.installArtifact(exe);

    // add a step to compile and run with `zig build run`
    const run_cmd = b.addRunArtifact(exe);
    // make running also install the executable to zig-out, not just in the cache
    run_cmd.step.dependOn(b.getInstallStep());
    // forward arguments to the program, if there are any, so that `zig build run -- [args]` works
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
