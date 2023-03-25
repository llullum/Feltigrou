import pytest
import subprocess


class Test_Pretty_Print():

    bin_path = "./../src/"
    cmd = bin_path + "tc"

    def exec_test(self, file, object=False, test_path = "our/"):
        
        print(self.cmd + " -XA " + test_path + file + " | " + self.cmd + " -XA -")
        
        if (not object):
            output = subprocess.run(
            [self.cmd, "-XA", test_path + file, "|", self.cmd, "-XA", "-"], capture_output=True, text=True)
        else:
            output = subprocess.run(
            [self.cmd, "-XoA", test_path + file, "|", self.cmd, "-XoA", "-"], capture_output=True, text=True)

        exit = output.returncode
        assert exit == 0
    
    def test_hello_world(self):
        self.exec_test("hello-world.tig")
        
    def test_simple_fact(self):
        self.exec_test("simple-fact.tig")
        
    def test_escape_epita(self):
        self.exec_test("escape-epita.tig")
        
    def test_precedence(self):
        self.exec_test("precedence.tig")
        
    def test_1s_and_2s(self):
        self.exec_test("1s-and-2s.tig")
        
    def test_for_loop(self):
        self.exec_test("for-loop.tig")
        
    def test_parens(self):
        self.exec_test("parens.tig")
        
    def test_simple_class(self):
        self.exec_test("simple-class.tig", True)
        
    def test_simple_class_given(self):
        self.exec_test("simple-class-given.tig", True)