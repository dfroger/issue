from os.path import abspath, join, dirname
import glob 

from pyximport import pyximport

def build_module(name, pyxfilename, pyxbuild_dir=None, inplace=False, language_level=None):
    # '$ROOT'
    here = abspath(dirname(__file__))

    # '$ROOT/build'
    build_dir = join(here, 'build')

    # ['foo', 'bar']
    paths = name.split('.')

    # 'bar'
    modname = paths.pop()

    # 'bar.*.so', to match 'bar.cpython-35m-x86_64-linux-gnu.so'
    filename_pattern = '%s.*.so' % modname

    # '/$ROOT/build/foo/bar.cpython-35m-x86_64-linux-gnu.so'
    pattern = join(build_dir, *paths, filename_pattern)

    # '$ROOT/build/foo/bar.cpython-35m-x86_64-linux-gnu.so'
    so_name = glob.glob(pattern)[0]

    print('getting module from waf build: %s' % so_name)

    return so_name

pyximport.build_module = build_module

pyximport.install()

from foo import bar

x = bar.baz(2)
print(x)
