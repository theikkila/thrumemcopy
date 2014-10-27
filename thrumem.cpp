#include <iostream>
#include <fstream>

using namespace std;
// This is how many pieces copier splits the file, one shard should not be bigger than available memory (because swapping sucks)
unsigned int divider = 3;

int main (int argc, char* argv[]) {

  unsigned int size_r, size;
  char * memblock;

  ifstream in (argv[1], ios::in|ios::binary|ios::ate);
  ofstream out(argv[2], ios::out|ios::binary);

  if (in.is_open() && out.is_open()) {
    size_r = in.tellg(); // this is the full size
    size = size_r / divider;
    memblock = new char [size];
    in.seekg (0, ios::beg);
    //(size_r - (size_r % divider) ) / divider
    for (int i = 0; i < divider; ++i){
      cout << "Reading " << size << " pieces to memory" << endl;
      in.read (memblock, size);
      cout << "Writing " << size << " pieces to file" << endl;
      out.write(memblock, size);
      cout << "-------------------------------------" << endl;
    }
    cout << "Whats left here? " << size_r % divider << " pieces of data. Lets copy those too..." << endl;
    cout << "Reading " << size_r % divider << endl;
    in.read (memblock, size_r % divider);
    cout << "Writing " << size_r % divider << endl;
    out.write(memblock, size_r%divider);
    in.close();
    out.close();
    cout << "Ready!" << endl;
    delete[] memblock;
  } else {
    cout << "Unable to open file" << endl;
    return -1;
  }
  return 0;
}