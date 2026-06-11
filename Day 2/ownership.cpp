#include <iostream>
#include <memory>
#include <utility>

class Resource {
public:
    Resource() {
        std::cout<<"acquired"<<std::endl;
    }

    ~Resource() {
        std::cout<<"released"<<std::endl;
    }
};

void take(const Resource& res){
    std::cout << "looking, not owning" <<std::endl;
}

int main() {
    std::unique_ptr<Resource> owner1 = std::make_unique<Resource>();

    take(*owner1);

    std::unique_ptr<Resource> owner2 = std::move(owner1);


    if (owner1 == nullptr){
        std::cout <<"owner1 is empty" <<std::endl;
    }

    return 0;
}
