#include<iostream>
using namespace std;
class FiboHeap {
public:
	class FiboNode {
	public:
		bool mark; //Decrease key 연산용
		FiboNode* par;
		FiboNode* bef;
		FiboNode* aft;
		FiboNode* child;
		int val;
		int degree;
		FiboNode(int _val) : mark(false), par(nullptr), bef(nullptr), aft(nullptr), child(nullptr), val(_val), degree(0) {
		}
	};
	FiboNode* min;
	int n;
	FiboHeap(): min(nullptr){}

	void insert(int num) { //단순 삽입
		FiboNode* nd = new FiboNode(num);
		if (!n) min = min->bef = min->aft = nd;
		else {
			min->bef->aft = nd;
			nd->bef = min->bef;
			min->bef = nd;
			nd->aft = min;
			if (num < min->val) min = nd;
		}
		++n;
	}

	void extract_min() { //코어
		FiboNode* nd = min->child;
		for (int i = 0; i < min->degree; i++) { //노드들 삽입
			FiboNode* tmp = nd->aft;
			min->bef->aft = nd;
			nd->bef = min->bef;
			min->bef = nd;
			nd->aft = min;
			nd->par = nullptr;
			nd = tmp;
		}
		min->bef->aft = min->aft;
		min->aft->bef = min->bef;
		if (min == min->aft) //min 밖에 없을 경우
			min = nullptr;
		else {
			FiboNode* ftmp = min->aft;
			while (ftmp != min) {
				FiboNode** consolidateArray = new FiboNode*[static_cast<int>(log(n)) + 1];
				if (consolidateArray[ftmp->degree]) {
					if (consolidateArray[ftmp->degree]->val > ftmp->val)
						swap(consolidateArray[ftmp->degree], ftmp);
					if (consolidateArray[ftmp->degree]->child == 0) {
						consolidateArray[ftmp->degree]->child = ftmp;
						ftmp->aft = ftmp->bef = ftmp;
					}
					else {
						consolidateArray[ftmp->degree]->child->bef->aft = ftmp;
						ftmp->bef = consolidateArray[ftmp->degree]->child->bef;
						consolidateArray[ftmp->degree]->child->bef = ftmp;
						ftmp->aft = consolidateArray[ftmp->degree]->child;
					}
					ftmp->par = consolidateArray[ftmp->degree];
					consolidateArray[ftmp->degree]->degree++;
				}
				else consolidateArray[ftmp->degree] = ftmp;
				ftmp = ftmp->aft;
			}
		}
	}
};
int main() {

	return 0;
}