import subprocess
import pytest
from glob import glob
from common import *

test_files = glob(f"{tests_path}/var/*.c")
expected_return_code = [0, 0, 1]


class TestVar:
    @pytest.mark.parametrize(
        "test_file, return_code",
        zip(test_files, expected_return_code),
    )
    def test_all(self, test_file, return_code):
        with open(test_file) as f:
            result = subprocess.run(interpretador, stdin=f)

            assert result.returncode == return_code
