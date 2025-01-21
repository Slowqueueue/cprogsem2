#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>>
using namespace std;

template <typename Iterator>
void insertion_sort(Iterator first, Iterator last)
{
    if (!(first < last)) return;

    for (Iterator i = first + 1; i != last; ++i)
        for (Iterator j = i; j != first && *j < *(j - 1); --j)
            std::iter_swap(j - 1, j);
}

int main()
{
    printf("Enter the sequence of numbers (Press Ctrl+Z to finish)\n");
    vector<double> seq;
    vector<double>::iterator iter;
    istream_iterator<double> cin_iter(cin), cin_end;
    int numcnt = 0;
    while (cin_iter != cin_end)
    {
        double d = *cin_iter;
        seq.push_back(d);
        cin_iter++;
        numcnt++;
    }
    if (numcnt == 0) return 0;

    insertion_sort(seq.begin(), seq.end());

    double* arrp = &seq[0];
    for (int i = 0; i < numcnt; i++) printf("%g ", arrp[i]);
    cin.get();
    return 0;
}