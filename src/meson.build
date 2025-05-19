sources = [
  'BinaryBuffer.cpp',
  'Config.cpp',
  'Constants.cpp',
  'Engine.cpp',
  'EngineMetadata.cpp',
  'EventEngine.cpp',
  'Game.cpp',
  'LuaInterop.cpp',
  'Main.cpp',
  'Panic.cpp',
  'Platform.cpp',
  'RenderingEngine.cpp',
  'Result.cpp',
  'Scene.cpp',
  'ScriptEngine.cpp',
  'Util.cpp',
  'State.cpp',
  'Util.cpp',
  'Vector2.cpp',
]

clang_tidy_target = custom_target('run_clang_tidy',
  input: sources,
  output: 'clang_tidy_report.txt',
  command: [
    'clang-tidy',
    '@INPUT@',
    '--',
    '-I', '.',
    '-std=c++20',
    '-checks=*',
    '-warnings-as-errors=*'
  ]
)

executable('eng', sources, dependencies: deps, include_directories: inc_dirs)

