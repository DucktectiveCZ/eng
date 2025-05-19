project('eng', 'cpp',
  version: '0.1',
  default_options: ['cpp_std=c++20', 'warning_level=3']
)

cc = meson.get_compiler('cpp')

sdl2_dep = dependency('sdl2')
sdl2_image_dep = dependency('SDL2_image')
sdl2_mixer_dep = dependency('SDL2_mixer')
sdl2_ttf_dep = dependency('SDL2_ttf')
spdlog_dep = dependency('spdlog')
tomlplusplus_dep = dependency('tomlplusplus')
tinyxml2_dep = dependency('tinyxml2', required: true)
lua_dep = dependency('luajit', required: true)
libatomic_dep = cc.find_library('atomic', required: false)

sol2_inc = include_directories('external/sol2/include/')
magic_enum_inc = include_directories('external/magic_enum/include/magic_enum/')

inc_dirs = [
  sol2_inc,
  magic_enum_inc,
]

deps = [
  sdl2_dep,
  sdl2_image_dep,
  sdl2_mixer_dep,
  sdl2_ttf_dep,
  spdlog_dep,
  tomlplusplus_dep,
  tinyxml2_dep,
  lua_dep,
]

if libatomic_dep.found()
  deps += libatomic_dep
endif

subdir('src')

