import aethermark as m

def test_main():
    print("Imported from:", m.__file__)
    assert m.__version__ == '0.1.0'
    assert m.add(1, 2) == 3
    assert m.subtract(1, 2) == -1
