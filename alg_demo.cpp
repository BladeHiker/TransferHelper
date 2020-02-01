#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>
#include <map>
#include <ctime>
using namespace std;
class Linelst;
class line;
class Station;
class StaLst;
class Path;
class TransMap;
class TransPath;
class MapTool;
class LineLst
{
public:
    LineLst();
    void push(line *l);
    vector<line *> &getList();

private:
    vector<line *> lineList;
};
class line
{
public:
    line(string name, string color, StaLst *slst, int way, double p, int bh, int bm, int eh, int em);
    string name();
    string color();
    StaLst *slist();
    int priceMethod();
    double price();
    void begTime(int &h, int &m);
    void endTime(int &h, int &m);

private:
    string lineName;
    string lineColor;
    StaLst *staList;
    int pPriceMethod; //区间计价 里程计价
    double pPrice;
    int begHour, begMin;
    int endHour, endMin;
};
class Station
{
public:
    Station(string name, bool chaSta, LineLst *llst, int lineCnt, ...);
    string name() const;
    int lineNum();
    bool isChaSta();
    bool isAble();

private:
    string staName;
    vector<line *> lines;
    bool chargeSta;
    bool accessAble;
};
class StaLst
{
public:
    void push(const Station &sta);
    int size();

private:
    vector<Station> staList;
};
class Path
{
public:
    Path(double len = 0, double time = 0, double price = 0, int way = 0) : pLength(len), pTime(time), pPrice(price), pPriceMethod(way) {}

private:
    int pPriceMethod; //区间计价 里程计价
    double pPrice;
    double pLength;
    double pTime;
};
class TransMap
{
public:
    void Push(string from, string to, Path &p, bool two_way);
    Path getPath(string from, string to);

private:
    map<pair<string, string>, Path> Map;
};
class TransPath
{
public:
    TransPath();
    double getTime();
    double getPrice();
    double getLength();
    double getTranstime();
    int getStanum();

private:
    double time;
    double length;
    double price;
    double tranferTimes;
    int staNum;
};
class MapTool
{
public:
    MapTool(TransMap &m, StaLst &l) : Map(m), allLst(l) {}
    double pathLenth(string from, string to);
    double timeLength(string from, string to);
    double pathPrice(string from, string to);
    bool reachable(string from, string to);
    vector<TransPath> getPathLst(string from, string to, bool (*cmp)(TransPath &a, TransPath &b));
    bool (*cmpCho(string arg))(TransPath &, TransPath &);

private:
    TransMap &Map;
    StaLst &allLst;
};

Station::Station(string name, bool chaSta, LineLst *llst, int lineCnt, ...)
{
    this->staName = name;
    this->chargeSta = chaSta;
    va_list ap;
    va_start(ap, lineCnt);
    for (int i = 0; i < lineCnt; ++i)
    {
        for (auto &ii : llst->getList())
        {
            if (ii->name() == va_arg(ap, string))
                lines.push_back(ii);
        }
    }
    va_end(ap);
}
string Station::name() const
{
    return this->staName;
}
int Station::lineNum()
{
    return lines.size();
}
bool Station::isChaSta()
{
    return this->chargeSta;
}
bool Station::isAble()
{
    return this->accessAble;
}
void StaLst::push(const Station &sta)
{
    staList.push_back(sta);
}
int StaLst::size()
{
    return staList.size();
}
LineLst::LineLst()
{
}
void LineLst::push(line *l)
{
    this->lineList.push_back(l);
}
vector<line *> &LineLst::getList()
{
    return this->lineList;
}
void TransMap::Push(string from, string to, Path &p, bool two_way = true)
{
    Map[make_pair(from, to)] = p;
    if (two_way)
        Map[make_pair(to, from)] = p;
}
Path TransMap::getPath(string from, string to)
{
    return Map[make_pair(from, to)];
}

line::line(string name, string color, StaLst *slst, int way, double p, int bh, int bm, int eh, int em)
{
    this->lineName = name;
    this->lineColor = color;
    this->staList = slst;
    this->pPriceMethod = way;
    this->pPrice = p;
    this->begHour = bh;
    this->begMin = bm;
    this->endHour = eh;
    this->endMin = em;
}
string line::name()
{
    return this->lineName;
}
string line::color()
{
    return this->lineColor;
}
StaLst *line::slist()
{
    return this->staList;
}
int line::priceMethod()
{
    return this->pPriceMethod;
}
double line::price()
{
    return this->pPrice;
}
void line::begTime(int &h, int &m)
{
    h = this->begHour;
    m = this->begMin;
}
void line::endTime(int &h, int &m)
{
    h = this->endHour;
    m = this->endMin;
}
bool (*MapTool::cmpCho(string arg))(TransPath &, TransPath &)
{
    //arg 123 时间 价格 换乘次数
    if (arg == "123")
        return [](TransPath &a, TransPath &b) {
            if (a.getTime() != b.getTime())
                return a.getTime() < b.getTime();
            if (a.getPrice() != b.getPrice())
                return a.getPrice() < b.getPrice();
            if (a.getTranstime() != b.getTranstime())
                return a.getTranstime() < b.getTranstime();
            return false;
        };
    if (arg == "132")
        return [](TransPath &a, TransPath &b) {
            if (a.getTime() != b.getTime())
                return a.getTime() < b.getTime();
            if (a.getTranstime() != b.getTranstime())
                return a.getTranstime() < b.getTranstime();
            if (a.getPrice() != b.getPrice())
                return a.getPrice() < b.getPrice();
            return false;
        };
    if (arg == "213")
        return [](TransPath &a, TransPath &b) {
            if (a.getPrice() != b.getPrice())
                return a.getPrice() < b.getPrice();
            if (a.getTime() != b.getTime())
                return a.getTime() < b.getTime();

            if (a.getTranstime() != b.getTranstime())
                return a.getTranstime() < b.getTranstime();
            return false;
        };
    if (arg == "231")
        return [](TransPath &a, TransPath &b) {
            if (a.getPrice() != b.getPrice())
                return a.getPrice() < b.getPrice();
            if (a.getTranstime() != b.getTranstime())
                return a.getTranstime() < b.getTranstime();
            if (a.getTime() != b.getTime())
                return a.getTime() < b.getTime();
            return false;
        };
    if (arg == "321")
        return [](TransPath &a, TransPath &b) {
            if (a.getTranstime() != b.getTranstime())
                return a.getTranstime() < b.getTranstime();
            if (a.getPrice() != b.getPrice())
                return a.getPrice() < b.getPrice();
            if (a.getTime() != b.getTime())
                return a.getTime() < b.getTime();
            return false;
        };
    if (arg == "312")
        return [](TransPath &a, TransPath &b) {
            if (a.getTranstime() != b.getTranstime())
                return a.getTranstime() < b.getTranstime();
            if (a.getTime() != b.getTime())
                return a.getTime() < b.getTime();
            if (a.getPrice() != b.getPrice())
                return a.getPrice() < b.getPrice();
            return false;
        };
    return nullptr;
}

int main()
{
    return 0;
}

double TransPath::getTime()
{
    return this->time;
}

double TransPath::getPrice()
{
    return this->price;
}

double TransPath::getLength()
{
    return this->length;
}

double TransPath::getTranstime()
{
    return this->tranferTimes;
}

int TransPath::getStanum()
{
    return this->staNum;
}
