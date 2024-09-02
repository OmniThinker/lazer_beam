project('lazer_beam', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

check = dependency('check', version: '>=0.15.2')
testSrc = ['test/main.c']
testExe = executable('tests', sources: testSrc, dependencies: check)
test('tests', testExe)

src = ['src/main.c', 'src/identifiers.c']
exe = executable('lazer_beam', sources: src,
  install : true)
