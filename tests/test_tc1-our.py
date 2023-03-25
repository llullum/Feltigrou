import pytest
import subprocess


class Test_TC1_our():

    bin_path = "./../src/"
    test_path = "our/ourgood/"
    cmd = bin_path + "tc"

    def exec_test(self, file, expected_exit=0, object=False):
        if (not object):
            output = subprocess.run(
            [self.cmd, "--parse", self.test_path + file], capture_output=True, text=True)
        else:
            output = subprocess.run(
            [self.cmd, "-o", "--parse", self.test_path + file], capture_output=True, text=True)

        exit = output.returncode

        assert exit == expected_exit

    def test_1s_and_2s(self):
        self.exec_test("1s-and-2s.tig")
        
    def test_and(self):
        self.exec_test("and.tig")

    def test_arithmetic_val(self):
        self.exec_test("arithmetic-val.tig")

    def test_arthimetic(self):
        self.exec_test("arthimetic.tig")
    
    def test_bad_octal(self):
        self.exec_test("bad-octal.tig",2)

    def test_big_buddy(self):
        self.exec_test("big-buddy.tig")
        
    def test_broken_comment(self):
        self.exec_test("broken-comment.tig", 2)
        
    def test_class_extend(self):
        self.exec_test("class-extend.tig", 0, True)

    def test_declare_my_variable(self):
        self.exec_test("declare-my-variable.tig")
        
    def test_escape_epita(self):
        self.exec_test("escape-epita.tig")
        
    def test_escaped_comma(self):
        self.exec_test("escaped-comma.tig", 2)

    def test_fibo(self):
        self.exec_test("fibo.tih")
        
    def test_for_loop(self):
        self.exec_test("for-loop.tig")

    def test_getchar(self):
        self.exec_test("getchar.tig")

    def test_hello_tigrou(self):
        self.exec_test("hello-tigrou.tig")

    def test_how_old_am_i(self):
        self.exec_test("how-old-am-i.tig")

    def test_if_and_if(self):
        self.exec_test("if-and-if.tig")

    def test_if(self):
        self.exec_test("if.tig")

    def test_let_if(self):
        self.exec_test("let-if.tig")

    def test_linked_list(self):
        self.exec_test("linked-list.tih")
        
    def test_or(self):
        self.exec_test("or.tig")
        
    def test_parens(self):
        self.exec_test("parens.tig")
        
    def test_precedence(self):
        self.exec_test("precedence.tig")
        
    def test_simple_class_given(self):
        self.exec_test("simple-class-given.tig", 0, True)
        
    def test_simple_class(self):
        self.exec_test("simple-class.tig", 0, True)
        
    def test_simple_fact(self):
        self.exec_test("simple-fact.tig")

    def test_sort(self):
        self.exec_test("sort.tih")
        
    def test_trivial(self):
        self.exec_test("trivial.tig")

    def test_unterminated_string(self):
        self.exec_test("unterminated-string.tig", 2)

    def test_use_an_array(self):
        self.exec_test("use-an-array.tih")

    def test_who_am_i(self):
        self.exec_test("who-am-i.tih")
