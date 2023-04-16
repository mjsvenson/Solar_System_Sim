#include "Universe.h"
using namespace std;

int main(int argc, char* argv[])
{

double time, del;

time = atof(argv[1]);
del = atof(argv[2]);

Universe u;
u.create(time, del);

return 0;
}
