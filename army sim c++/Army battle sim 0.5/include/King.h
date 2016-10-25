#ifndef KING_H
#define KING_H

#include <string>
#include <Unit.h>


class King : public Unit
{
    public:
        King(Army* parentArmy, std::string kingName);
        virtual ~King();
        void unitMove(Map2D* battleMap, std::vector<Army*> Armies);
        void kingMove(Map2D* battleMap, std::vector<Army*> Armies);

        std::string getName() { return name; };
    protected:
    private:
        std::string name;
};

#endif // KING_H
