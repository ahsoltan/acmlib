export TEXINPUTS=.:tex/:
export PYTHONDONTWRITEBYTECODE=1

main: build
	pdflatex -shell-escape -output-directory build/ content/main.tex
	cp build/main.pdf main.pdf

build:
	mkdir -p build/

.PHONY: clean
clean:
	trash -rf build
