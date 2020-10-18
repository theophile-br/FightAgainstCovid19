all: clean prepare build

clean:
	rm -R ./out

prepare:
	mkdir -p out

build:
	g++ -g -std=c++17 -Wall src/main.cpp src/train.cpp src/predict.cpp -o out/pbl_masked `pkg-config --cflags --libs opencv4`

gt: all rungraytrain

gp: all rungraypredict

ct: all runcolortrain

cp: all runcolorpredict

rungraytrain:
	./out/pbl_masked -t train -m gray datasets 

rungraypredict:
	./out/pbl_masked -t predict -m gray datasets

runcolortrain:
	./out/pbl_masked -t train -m color datasets 

runcolorpredict:
	./out/pbl_masked -t predict -m color datasets