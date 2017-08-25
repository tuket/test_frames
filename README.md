This is a minimal project for a [question in stackoverflow](https://stackoverflow.com/questions/45885534/sdl-opengl-irregular-frame-times-with-periodic-spikes).

In order to compile this project you need CMake
```
mkdir build 
cd build
cmake ..
make
```

All the code is in `main.cpp`. The program makes a list of delta times (in milliseconds) and stores it in a file called `out.txt`.

Then I use python to load `out.txt` and plot the data:

```
def loadNums():
	f = open("out.txt")
	txt = f.read()
	numbers = txt.split('\n')
	numbers.pop()
	numbers = list(map(int, numbers))
	return numbers
	
numbers = loadNums()
xaxis = [0]
for y in numbers[:-1]:
	xaxis.append(xaxis[-1] + y)
plt.plot(xaxis, numbers)
plt.show()
```
