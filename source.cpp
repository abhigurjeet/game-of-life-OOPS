#include <bits/stdc++.h>
#include<climits>
using namespace std;
class GameOfLife{
private:
	map<int,bool> alive_cells;
	map<int,bool> neighbour_dead_cells;
	vector<int> new_alive_cells;
    int MAX_ROWS=1000;
    int MAX_COLS=100;
public:

	//Initialise constructor, can set rows and columns as per need.
	GameOfLife(){}
    
    //Get coordinates of alive cells
	void GetAliveCells(){
		cout<<"Please enter total number of alive cells and their coordinates separated by spaces"<<endl;
		int total_alive_cells;
		cin>>total_alive_cells;
		for(int i=0;i<total_alive_cells;i++){
			int row,col;
			cin>>row>>col;
			int position_on_1d=this->ConvertTo1Dcoordinate(row,col);
			alive_cells[position_on_1d]=1;
		}
	}

	//Check and add neighbour cells for inspection, these are the cells who state might change
	void CheckNeighbourCell(int row,int col){
		int position_on_1d=this->ConvertTo1Dcoordinate(row,col);
		if(alive_cells.find(position_on_1d)==alive_cells.end()&&neighbour_dead_cells[position_on_1d]!=1){
			neighbour_dead_cells[position_on_1d]=1;
		}
	}
	void AddNeighbourDeadCell(){
		for(auto i=alive_cells.begin();i!=alive_cells.end();i++){
			int row=ConvertTo2Dcoordinate(i->first).first;
			int col=ConvertTo2Dcoordinate(i->first).second;
			vector<pair<int, int>> directions = {
				{1, 0}, {1, 1}, {1, -1}, {0, 1},
				{0, -1}, {-1, 0}, {-1, 1}, {-1, -1}
			};
			for (const auto& dir : directions) {
				int newRow = row + dir.first;
				int newCol = col + dir.second;
				this->CheckNeighbourCell(newRow,newCol);
			}
		}
	}

	//Convert coordinate in a number which can be represented on a straight line
	int ConvertTo1Dcoordinate(int row,int col){
		int position_on_1d=(row)*MAX_COLS+col;
		return position_on_1d;
	}

	//Convert coordinates back to their original state
	pair<int,int> ConvertTo2Dcoordinate(int position_on_1d){
		int row=position_on_1d/MAX_COLS;
		int col=position_on_1d%MAX_COLS;
		return {row,col};
	}


	//Iterate all the alive cells and neighbour dead cells
	void UpdateCellStatus(){
		for(auto i=alive_cells.begin();i!=alive_cells.end();i++){
			int count=this->CountNeighbourAliveCells(i->first);
			if(count==2||count==3){
				new_alive_cells.push_back(i->first);
			}
		}
		for(auto i=neighbour_dead_cells.begin();i!=neighbour_dead_cells.end();i++){
			int count=this->CountNeighbourAliveCells(i->first);
			if(count==3){
				new_alive_cells.push_back(i->first);
			}
		}
	}

	//Get count of alive cells around a particular cell
	int CountNeighbourAliveCells(int position_on_1d){
		int row=this->ConvertTo2Dcoordinate(position_on_1d).first;
		int col=this->ConvertTo2Dcoordinate(position_on_1d).second;
		int count=0;
		vector<pair<int, int>> directions = {
            {1, 0}, {1, 1}, {1, -1}, {0, 1},
            {0, -1}, {-1, 0}, {-1, 1}, {-1, -1}
        };

        for (const auto& dir : directions) {
            int newRow = row + dir.first;
            int newCol = col + dir.second;
            int newPos = ConvertTo1Dcoordinate(newRow, newCol);
            if (alive_cells.find(newPos) != alive_cells.end()) {
                count++;
            }
        }
		return count;
	}

	//Print the final list of alive cells after 1 tick
	void PrintCellsList(){
		cout<<"Alive cells are"<<endl;
		for(int i=0;i<new_alive_cells.size();i++){
			int row=ConvertTo2Dcoordinate(new_alive_cells[i]).first;
			int col=ConvertTo2Dcoordinate(new_alive_cells[i]).second;
			cout<<row<<" "<<col<<endl;
		}
	}
};
int main() {
	GameOfLife firstGame;
	firstGame.GetAliveCells();
	firstGame.AddNeighbourDeadCell();
	firstGame.UpdateCellStatus();
	firstGame.PrintCellsList();
	return 0;
}