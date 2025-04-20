project('eng', 'cpp',
  version: '0.1',
  default_options: ['cpp_std=c++20', 'cxx_flags=-fno-exceptions']
)

sdl2_dep = dependency('sdl2')
sdl2_image_dep = dependency('SDL2_image')
sdl2_mixer_dep = dependency('SDL2_mixer')
sdl2_ttf_dep = dependency('SDL2_ttf')
spdlog_dep = dependency('spdlog')
tomlplusplus_dep = dependency('tomlplusplus')
tinyxml2_dep = dependency('tinyxml2', required: true)
lua_dep = dependency('lua', required: true)

deps = [
  sdl2_dep,
  sdl2_image_dep,
  sdl2_mixer_dep,
  sdl2_ttf_dep,
  spdlog_dep,
  tomlplusplus_dep,
  tinyxml2_dep,
  lua_dep
]

subdir('src')

