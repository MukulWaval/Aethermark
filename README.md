# Aethermark

[![Test](https://github.com/MukulWaval/Aethermark/actions/workflows/test.yml/badge.svg)](https://github.com/MukulWaval/Aethermark/actions/workflows/test.yml)

Aethermark is a high-performance, extensible Markdown parser and renderer designed with Aether-flavored Markdown (AFM), a custom dialect that enhances standard Markdown with additional features and improved rendering capabilities.

## Installation

You can install Aethermark from PyPI once published:

```sh
pip install aethermark
```

Alternatively, to install from source:

```sh
git clone https://github.com/MukulWaval/aethermark.git
cd aethermark
pip install .
```

## Building from Source

Using a virtual environment prevents conflicts with system-wide dependencies.

```bash
python3 -m venv .venv
source .venv/bin/activate  # On Windows: venv\Scripts\activate
pip install --upgrade pip setuptools wheel pytest
```

Always remove old build artifacts before building to prevent stale binaries from interfering.

```bash
rm -rf build dist *.egg-info
python3 setup.py clean
python3 setup.py sdist bdist_wheel --universal
```

## Testing

Instead of running tests inside the build directory, install the generated wheel and test it as an installed package (like your users would).

```bash
pip install --force-reinstall --no-cache-dir dist/aethermark-*.tar.gz
pytest
```

## Automating Releases with GitHub Actions

To trigger a release manually:

1. Push a new commit with an updated `VERSION` file.
2. Run the `publish.yml` GitHub Action workflow.

## Contributing

Pull requests are welcome! Please ensure your changes follow the project structure and best practices.

## License

MIT License. See `LICENSE` for details.
