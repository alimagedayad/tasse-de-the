#include "Node.h"
#include <iomanip>
node::node(int num, std::string tsk, std::string ctg, int cnt) {
    task = tsk;
    number = num;
    category = ctg;
    ID = cnt;
    prev = nullptr;
    next = nullptr;

}
std::ostream& operator<<(std::ostream& out, node const object) {
    out << "|" << std::setfill(' ')<<std::setw(5) << "|"<<object.ID << "|" << std::setfill(' ') << std::setw(20) << "|" << object.number << "|" << std::setfill(' ') << std::setw(20) << "|" << object.category << "|" << std::setfill(' ') << std::setw(30) << "|" << object.task << "|" <<std::setw(10)<<"|"<< std::endl;
    return out;
}