import nose.tools
nose.tools.assert_multi_line_equal.im_class.maxDiff = None

import codegen
import formast
import integers

def test_codegen():
    top = formast.Top()
    with open("integers.xml", "rb") as stream:
        formast.XmlParser().parse_string(stream.read(), top)
    codegen_module = codegen.CodeGenModule()
    codegen_module.top(top)
    with open("integers.py", "rb") as stream:
        nose.tools.assert_multi_line_equal(stream.read(), str(codegen_module))

def test_ver0_1():
    data = integers.IntegerData()
    with open("test_ver0_1.integers", "rb") as stream:
        data.read(stream)
        eof_check = stream.read(1)
    nose.tools.assert_equal(eof_check, '')
    nose.tools.assert_equal(data.version, 0)
    nose.tools.assert_equal(data.has_integers, 1)
    nose.tools.assert_equal(data.has_integers_2, 0)
    nose.tools.assert_equal(data.num_integers, 3)
    nose.tools.assert_list_equal(data.integers, [3, 1, 4])
    nose.tools.assert_equal(data.num_integers_2, 0)
    nose.tools.assert_list_equal(data.integers_2, [])

def test_ver2_1():
    data = integers.IntegerData()
    with open("test_ver2_1.integers", "rb") as stream:
        data.read(stream)
        eof_check = stream.read(1)
    nose.tools.assert_equal(eof_check, '')
    nose.tools.assert_equal(data.version, 2)
    nose.tools.assert_equal(data.has_integers, 1)
    nose.tools.assert_equal(data.has_integers_2, 1)
    nose.tools.assert_equal(data.num_integers, 3)
    nose.tools.assert_list_equal(data.integers, [3, 1, 4])
    nose.tools.assert_equal(data.num_integers_2, 5)
    nose.tools.assert_list_equal(data.integers_2, [2, 7, 1, 8, 2])
