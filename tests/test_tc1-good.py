import pytest
import subprocess


class Test_TC1_good():

    bin_path = "./../src/"
    test_path = "good/"
    cmd = bin_path + "tc"

    def exec_test(self, file, expected_exit=0):
        output = subprocess.run(
            [self.cmd, "--parse", self.test_path + file], capture_output=True, text=True)
        exit = output.returncode
        text = output.stderr
        assert exit == expected_exit and text == ""

    def test_array_of_alias(self):
        self.exec_test("array-of-alias.tig")

    def test_array(self):
        self.exec_test("array.tig")

    def test_break_in_while(self):
        self.exec_test("break-in-while.tig")

    def test_comments_nested(self):
        self.exec_test("comments-nested.tig")

    def test_compare_record_and_nil(self):
        self.exec_test("compare-record-and-nil.tig")

    def test_fact(self):
        self.exec_test("fact.tig")

    def test_for_in_let(self):
        self.exec_test("for-in-let.tig")

    def test_fun_vs_var(self):
        self.exec_test("fun-vs-var.tig")

    def test_if(self):
        self.exec_test("if.tig")

    def test_local_vs_global_type(self):
        self.exec_test("local-vs-global-type.tig")

    def test_merge(self):
        self.exec_test("merge.tig")

    def test_mutually_recursive_functions(self):
        self.exec_test("mutually-recursive-functions.tig")

    def test_mutually_recursive_procedures(self):
        self.exec_test("mutually-recursive-procedures.tig")

    def test_queens(self):
        self.exec_test("queens.tig")

    def test_record(self):
        self.exec_test("record.tig")

    def test_recursive_types(self):
        self.exec_test("recursive-types.tig")

    def test_shadowing_functions(self):
        self.exec_test("shadowing-functions.tig")

    def test_shadowing_types_separate(self):
        self.exec_test("shadowing-types-separate.tig")

    def test_test27(self):
        self.exec_test("test27.tig")

    def test_test30(self):
        self.exec_test("test30.tig")

    def test_test37(self):
        self.exec_test("test37.tig")

    def test_test42(self):
        self.exec_test("test42.tig")

    def test_test44(self):
        self.exec_test("test44.tig")

    def test_test64_tig(self):
        self.exec_test("test64.tig")

    def test_test64_tih(self):
        self.exec_test("test64.tih")

    def test_three_name_spaces(self):
        self.exec_test("three-name-spaces.tig")
