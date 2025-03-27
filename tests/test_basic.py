from re import A
import pytest
import aethermark as m

def test_version():
    assert m.__version__ == '0.0.1'

if __name__ == "__main__":
    pytest.main()
    