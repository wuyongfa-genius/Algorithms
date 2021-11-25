// You are given a set of n types of rectangular 3-D boxes, where the i^th box has
// height h(i), width w(i) and depth d(i) (all real numbers). You want to create a stack
// of boxes which is as tall as possible, but you can only stack a box on top of another
// box if the dimensions of the 2-D base of the lower box are each strictly larger than
// those of the 2-D base of the higher box. Of course, you can rotate a box so that any
// side functions as its base. It is also allowable to use multiple instances of the same type of box.
#include <bits/stdc++.h>
using namespace std;

struct Box
{
    int h, w, d;
};

bool myCompare(Box &b1, Box &b2)
{
    return (b1.w * b1.d) > (b2.w * b2.d);
}

int maxStackHeight(const vector<Box> &boxes)
{
    int n = boxes.size();
    //generate all possible boxes after rotation
    vector<Box> rot(n * 3);
    int index = 0;
    for (int i = 0; i < n; ++i)
    {
        int h = boxes[i].h, w = boxes[i].w, d = boxes[i].d;
        rot[index].h = h;
        rot[index].w = min(w, d);
        rot[index].d = max(w, d);
        ++index;
        rot[index].h = w;
        rot[index].w = min(h, d);
        rot[index].d = max(h, d);
        ++index;
        rot[index].h = d;
        rot[index].w = min(w, h);
        rot[index].d = max(w, h);
        ++index;
    }
    sort(rot.begin(), rot.end(), myCompare); //sorting base area in decreasing order
    n = 3 * n;
    vector<int> msh(n);
    for (int i = 0; i < n; ++i)
        msh[i] = rot[i].h;
    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        { //base area of rot[j] is bigger than rot[i]
            if (rot[j].d > rot[i].d && rot[j].w > rot[i].w && msh[j] + rot[i].h > msh[i])
                msh[i] = msh[j] + rot[i].h;
        }
    }
    return *max_element(msh.begin(), msh.end());
}

/* Driver program to test above function */
int main()
{
    vector<Box> arr = {{4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32}};

    printf("The maximum possible height of stack is %d\n",
           maxStackHeight(arr));

    return 0;
}