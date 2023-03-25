import pytest
import subprocess


class Test_TC1_syntax():

    bin_path = "./../src/"
    test_path = "syntax/"
    cmd = bin_path + "tc"

    def exec_test(self, file, expected_exit=0):
        output = subprocess.run(
            [self.cmd, "--parse", self.test_path + file], capture_output=True, text=True)
        exit = output.returncode

        assert exit == expected_exit

    def test_array_of_alias(self):
        self.exec_test("typeid.tig", 3)
