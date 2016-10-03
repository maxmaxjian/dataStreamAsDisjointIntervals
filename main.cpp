#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <climits>
#include <algorithm>

using std::vector;

class Interval {
  public:
    int start, end;
    Interval(int s, int e) : start(s), end(e){}
    Interval() { Interval(0,0); }

    size_t hash() const {
        return std::hash<int>()(start)^std::hash<int>()(end);
    }

    bool operator<(const Interval & other) const {
        return start < other.start && end < other.end;
    }

    void print() const {
        std::cout << "(" << start << "," << end << ")";
    }
};

class SummaryRanges {
  public:
    SummaryRanges() {}

    void addNum(int val) {
        Interval itv(val, val);
        vector<Interval> adjs = getAdjs(itv);
        for (auto it : adjs)
            intvls.erase(it);
        adjs.push_back(itv);
        intvls.insert(merge(adjs));
    }

    vector<Interval> getIntervals() {
        vector<Interval> result;
        for (auto it = intvls.begin(); it != intvls.end(); ++it)
            result.push_back(*it);
        return result;
    }

  private:
    std::set<Interval> intvls;

    vector<Interval> getAdjs(const Interval & intv) {
        vector<Interval> result;
        for (auto it = intvls.begin(); it != intvls.end(); ++it) {
            if (it->end == intv.start-1)
                result.push_back(*it);
            else if (it->start <= intv.start && it->end >= intv.end)
                result.push_back(*it);
            else if (it->start == intv.end+1)
                result.push_back(*it);
        }
        return result;
    }

    Interval merge(const vector<Interval> & adj_intvs) {
        Interval result;
        int lower = INT_MAX, upper = INT_MIN;
        for (auto itv : adj_intvs) {
            if (itv.start < lower)
                lower = itv.start;
            if (itv.end > upper)
                upper = itv.end;
        }
        if (lower <= upper) {
            result.start = lower;
            result.end = upper;
        }
        return result;
    }
};

int main() {
    vector<int> dataStrm{1,3,7,2,6};

    SummaryRanges sumRanges;
    for (size_t i = 0; i < dataStrm.size(); ++i) {
        sumRanges.addNum(dataStrm[i]);
        auto vec = sumRanges.getIntervals();
        std::cout << "Current intervals are:\n";
        std::for_each(vec.begin(), vec.end(),
                      [](Interval & itv){
                          itv.print();
                      });
        std::cout << std::endl;
    }
}
