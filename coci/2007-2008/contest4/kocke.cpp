#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <stdlib.h>
#include <algorithm>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int ma3x[64][64];
int level[64][64];
PII prv[64][64];

void read() {
	int x, y;
	for(int i = 0; i < 5; i ++) {
		cin >> x >> y;
		x += 30, y += 30;
		ma3x[y][x] = 1;
	}
	
	ma3x[30][30] = 2;
}

PII findRobot() {
	for(int i = 1; i <= 60; i ++)
		for(int j = 1; j <= 60; j ++)
			if(ma3x[i][j] == 2)
				return mp(i, j);
	return mp(-1, -1);
}

void bfs(PII cur) {
	memset(level, -1, sizeof(level));
	queue< PII > q;
	
	for(int i = 0; i <= 62; i ++)
		for(int j = 0; j <= 62; j ++)
			prv[i][j] = mp(-1, -1);
	
	q.push(cur);
	level[cur.first][cur.second] = 0;
	while(!q.empty()) {
		PII tmp = q.front();
		q.pop();
		
		for(int k = 0; k < 4; k ++) {
			int x = tmp.first + dx[k];
			int y = tmp.second + dy[k];
			
			if(x >= 0 && x <= 62 && y >= 0 && y <= 62 && !ma3x[x][y] && level[x][y] == -1) {
				level[x][y] = level[tmp.first][tmp.second] + 1;
				prv[x][y] = tmp;
				q.push(mp(x, y));
			}
		}
	}
}

void moveRobot(PII oldPos, PII newPos) {
	ma3x[oldPos.first][oldPos.second] = 0;
	ma3x[newPos.first][newPos.second] = 2;
	
	if(oldPos.first == newPos.first) {
		if(oldPos.second + 1 == newPos.second) printf("R");
		else printf("L");
	}
	else {
		if(oldPos.first + 1 == newPos.first) printf("U");
		else printf("D");
	}
}

void findPath(PII start, PII end) {
	PII cur = end;
	vector< PII > vec;
	
	while(cur != mp(-1, -1)) {
		vec.pb(cur);
		cur = prv[cur.first][cur.second];
	}
	
	reverse(vec.begin(), vec.end());
	
	for(int i = 0; i < vec.size() - 1; i ++)
		moveRobot(vec[i], vec[i + 1]);
}

void go(PII target) {
	for(int i = 0; i <= 62; i ++)
		for(int j = 0; j <= 62; j ++)
			if(ma3x[i][j] == 2) {
				bfs(mp(i, j));
				findPath(mp(i, j), target);
				return;
			}
}

PII findBase() {
	for(int i = 20; i <= 40; i ++)
		for(int j = 20; j <= 40; j ++)
			if(ma3x[i][j] == 1)
				return mp(i, j);
	return mp(-1, -1);
}

PII findBase2() {
	for(int i = 20; i <= 40; i ++)
		for(int j = 20; j <= 40; j ++)
			if(ma3x[i][j] == 0 && ma3x[i][j + 1] == 1 && ma3x[i][j - 1] == 1 && ma3x[i + 1][j] == 1 && ma3x[i - 1][j] == 1)
				return mp(i, j);
	return mp(-1, -1);
}

void solve2() {
	PII cen = findBase2();
	PII box;
	
	go(mp(cen.first + 2, cen.second));
	PII rob = mp(cen.first + 2, cen.second);
	moveRobot(rob, mp(rob.first - 1, rob.second));
	ma3x[cen.first][cen.second] = 1;
	
	if(ma3x[60][1] == 1) {
		go(mp(61, 1));
		rob = mp(61, 1);
		box = mp(60, 1);
		while(box.first != 1) {
			moveRobot(rob, box);
			rob = box;
			box.first --;
			ma3x[box.first][box.second] = 1;
		}
	}
	
	if(ma3x[60][60] == 1) {
		go(mp(61, 60));
		rob = mp(61, 60);
		box = mp(60, 60);
		while(box.first != 1) {
			moveRobot(rob, box);
			rob = box;
			box.first --;
			ma3x[box.first][box.second] = 1;
		}
	}
	
	if(ma3x[1][60] == 1) {
		go(mp(1, 61));
		rob = mp(1, 61);
		box = mp(1, 60);
		while(box.second != 1) {
			moveRobot(rob, box);
			rob = box;
			box.second --;
			ma3x[box.first][box.second] = 1;
		}
	}
	
	go(mp(1, 0));
	rob = mp(1, 0);
	box = mp(1, 1);
	while(box.second != cen.second) {
		moveRobot(rob, box);
		rob = box;
		box.second ++;
		ma3x[box.first][box.second] = 1;
	}
	
	ma3x[rob.first][rob.second] = 0;
	printf("DR");
	rob.first --;
	rob.second ++;
	while(box.first != cen.first - 2) {
		moveRobot(rob, box);
		rob = box;
		box.first ++;
		ma3x[box.first][box.second] = 1;
	}
}

void solve() {
	for(int iter = 0; iter < 4; iter ++) {
		PII robotPos = findRobot();
		
		if(robotPos == mp(-1, -1)) {
			cout << "Can't find the robot!\n";
			exit(0);
		}
		
		bfs(robotPos);
		
		bool found = false;
		
		PII cubePos = mp(-1, -1);
		int dir = -1;
		
		for(int i = 20; i <= 40 && !found; i ++)
			for(int j = 20; j <= 40 && !found; j ++)
				if(ma3x[i][j] == 1) {
					if(level[i][j - 1] != -1) {
						bool fl = true;
						for(int k = j + 1; k <= 60; k ++)
							if(ma3x[i][k] == 1 || ma3x[i - 1][k] == 1 || ma3x[i + 1][k] == 1) {
								fl = false;
								break;
							}
						
						if(fl) {
							cubePos = mp(i, j);
							dir = 1;
							found = true;
							break;
						}
					}
					
					if(level[i][j + 1] != -1) {
						bool fl = true;
						for(int k = j - 1; k >= 0; k --)
							if(ma3x[i][k] == 1 || ma3x[i - 1][k] == 1 || ma3x[i + 1][k] == 1) {
								fl = false;
								break;
							}
						
						if(fl) {
							cubePos = mp(i, j);
							dir = 2;
							found = true;
							break;
						}
					}
					
					if(level[i - 1][j] != -1) {
						bool fl = true;
						for(int k = i + 1; k <= 60; k ++)
							if(ma3x[k][j] == 1 || ma3x[k][j - 1] == 1 || ma3x[k][j + 1] == 1) {
								fl = false;
								break;
							}
						
						if(fl) {
							cubePos = mp(i, j);
							dir = 3;
							found = true;
							break;
						}
					}
					
					if(level[i + 1][j] != -1) {
						bool fl = true;
						for(int k = i - 1; k >= 0; k --)
							if(ma3x[k][j] == 1 || ma3x[k][j - 1] == 1 || ma3x[k][j + 1] == 1) {
								fl = false;
								break;
							}
						
						if(fl) {
							cubePos = mp(i, j);
							dir = 4;
							found = true;
							break;
						}
					}
				}
		
		if(found) {
			PII targetPos = cubePos;
			if(dir == 1) targetPos.second --;
			else if(dir == 2) targetPos.second ++;
			else if(dir == 3) targetPos.first --;
			else if(dir == 4) targetPos.first ++;
			
			findPath(robotPos, targetPos);
			robotPos = targetPos;
			
			if(dir == 1) {
				while(cubePos.second != 60) {
					moveRobot(robotPos, cubePos);
					robotPos = cubePos;
					cubePos.second ++;
					ma3x[cubePos.first][cubePos.second] = 1;
				}
				
				if(ma3x[1][60] == 0) {
					ma3x[robotPos.first][robotPos.second] = 0;
					printf("UR");
					robotPos.first ++;
					robotPos.second ++;
					while(cubePos.first != 1) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.first --;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
				}
				else if(ma3x[60][60] == 0) {
					ma3x[robotPos.first][robotPos.second] = 0;
					printf("DR");
					robotPos.first --;
					robotPos.second ++;
					while(cubePos.first != 60) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.first ++;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
				}
				else {
					ma3x[robotPos.first][robotPos.second] = 0;
					printf("URRD");
					robotPos.second += 2;
					while(cubePos.second != 50) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.second --;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
					
					if(ma3x[1][1] == 0) {
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("UL");
						robotPos.first ++;
						robotPos.second --;
						while(cubePos.first != 1) {
							moveRobot(robotPos, cubePos);
							robotPos = cubePos;
							cubePos.first --;
							ma3x[cubePos.first][cubePos.second] = 1;
						}
						
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("RD");
						robotPos.first --;
						robotPos.second ++;
					}
					else if(ma3x[60][1] == 0) {
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("DL");
						robotPos.first --;
						robotPos.second --;
						while(cubePos.first != 60) {
							moveRobot(robotPos, cubePos);
							robotPos = cubePos;
							cubePos.first ++;
							ma3x[cubePos.first][cubePos.second] = 1;
						}
						
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("RU");
						robotPos.first ++;
						robotPos.second ++;
					}
					
					while(cubePos.second != 1) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.second --;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
				}
			}
			else if(dir == 2) {
				while(cubePos.second != 1) {
					moveRobot(robotPos, cubePos);
					robotPos = cubePos;
					cubePos.second --;
					ma3x[cubePos.first][cubePos.second] = 1;
				}
				
				if(ma3x[1][1] == 0) {
					ma3x[robotPos.first][robotPos.second] = 0;
					printf("UL");
					robotPos.first ++;
					robotPos.second --;
					while(cubePos.first != 1) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.first --;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
				}
				else if(ma3x[60][1] == 0) {
					ma3x[robotPos.first][robotPos.second] = 0;
					printf("DL");
					robotPos.first --;
					robotPos.second --;
					while(cubePos.first != 60) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.first ++;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
				}
				else {
					ma3x[robotPos.first][robotPos.second] = 0;
					printf("ULLD");
					robotPos.second -= 2;
					while(cubePos.second != 10) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.second ++;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
					
					if(ma3x[1][60] == 0) {
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("UR");
						robotPos.first ++;
						robotPos.second ++;
						while(cubePos.first != 1) {
							moveRobot(robotPos, cubePos);
							robotPos = cubePos;
							cubePos.first --;
							ma3x[cubePos.first][cubePos.second] = 1;
						}
						
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("LD");
						robotPos.first --;
						robotPos.second --;
					}
					else if(ma3x[60][60] == 0) {
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("DR");
						robotPos.first --;
						robotPos.second ++;
						while(cubePos.first != 60) {
							moveRobot(robotPos, cubePos);
							robotPos = cubePos;
							cubePos.first ++;
							ma3x[cubePos.first][cubePos.second] = 1;
						}
						
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("LU");
						robotPos.first ++;
						robotPos.second --;
					}
					
					while(cubePos.second != 60) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.second ++;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
				}
			}
			else if(dir == 3) {
				while(cubePos.first != 60) {
					moveRobot(robotPos, cubePos);
					robotPos = cubePos;
					cubePos.first ++;
					ma3x[cubePos.first][cubePos.second] = 1;
				}
				
				if(ma3x[60][1] == 0) {
					ma3x[robotPos.first][robotPos.second] = 0;
					printf("RU");
					robotPos.first ++;
					robotPos.second ++;
					
					while(cubePos.second != 1) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.second --;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
				}
				else if(ma3x[60][60] == 0) {
					ma3x[robotPos.first][robotPos.second] = 0;
					printf("LU");
					robotPos.first ++;
					robotPos.second --;
					
					while(cubePos.second != 60) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.second ++;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
				}
				else {
					ma3x[robotPos.first][robotPos.second] = 0;
					printf("LUUR");
					robotPos.first += 2;
					while(cubePos.first != 50) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.first --;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
					
					if(ma3x[1][1] == 0) {
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("RD");
						robotPos.first --;
						robotPos.second ++;
						while(cubePos.second != 1) {
							moveRobot(robotPos, cubePos);
							robotPos = cubePos;
							cubePos.second --;
							ma3x[cubePos.first][cubePos.second] = 1;
						}
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("UL");
						robotPos.first ++;
						robotPos.second --;
					}
					else if(ma3x[1][60] == 0) {
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("LD");
						robotPos.first --;
						robotPos.second --;
						while(cubePos.second != 60) {
							moveRobot(robotPos, cubePos);
							robotPos = cubePos;
							cubePos.second ++;
							ma3x[cubePos.first][cubePos.second] = 1;
						}
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("UR");
						robotPos.first ++;
						robotPos.second ++;
					}
					
					while(cubePos.first != 1) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.first --;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
				}
			}
			else if(dir == 4) {
				while(cubePos.first != 1) {
					moveRobot(robotPos, cubePos);
					robotPos = cubePos;
					cubePos.first --;
					ma3x[cubePos.first][cubePos.second] = 1;
				}
				
				if(ma3x[1][1] == 0) {
					ma3x[robotPos.first][robotPos.second] = 0;
					printf("RD");
					robotPos.first --;
					robotPos.second ++;
					
					while(cubePos.second != 1) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.second --;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
				}
				else if(ma3x[1][60] == 0) {
					ma3x[robotPos.first][robotPos.second] = 0;
					printf("LD");
					robotPos.first --;
					robotPos.second --;
					
					while(cubePos.second != 60) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.second ++;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
				}
				else {
					ma3x[robotPos.first][robotPos.second] = 0;
					printf("LDDR");
					robotPos.first -= 2;
					while(cubePos.first != 10) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.first ++;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
					
					if(ma3x[60][1] == 0) {
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("RU");
						robotPos.first ++;
						robotPos.second ++;
						while(cubePos.second != 1) {
							moveRobot(robotPos, cubePos);
							robotPos = cubePos;
							cubePos.second --;
							ma3x[cubePos.first][cubePos.second] = 1;
						}
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("DL");
						robotPos.first --;
						robotPos.second --;
					}
					else if(ma3x[60][60] == 0) {
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("LU");
						robotPos.first ++;
						robotPos.second --;
						while(cubePos.second != 60) {
							moveRobot(robotPos, cubePos);
							robotPos = cubePos;
							cubePos.second ++;
							ma3x[cubePos.first][cubePos.second] = 1;
						}
						ma3x[robotPos.first][robotPos.second] = 0;
						printf("DR");
						robotPos.first --;
						robotPos.second ++;
					}
					
					while(cubePos.first != 60) {
						moveRobot(robotPos, cubePos);
						robotPos = cubePos;
						cubePos.first ++;
						ma3x[cubePos.first][cubePos.second] = 1;
					}
				}
			}
		}
		else {
			solve2();
			return;
		}
	}
	
	PII cell = findBase();
	PII rob, box;
	
	/// First box
	go(mp(1, 0));
	rob = mp(1, 0);
	box = mp(1, 1);
	while(box.second != cell.second) {
		moveRobot(rob, box);
		rob = box;
		box.second ++;
		ma3x[box.first][box.second] = 1;
	}
	
	ma3x[rob.first][rob.second] = 0;
	printf("DR");
	rob.first --;
	rob.second ++;
	
	while(box.first != cell.first - 1) {
		moveRobot(rob, box);
		rob = box;
		box.first ++;
		ma3x[box.first][box.second] = 1;
	}
	
	/// Second box
	go(mp(1, 61));
	rob = mp(1, 61);
	box = mp(1, 60);
	while(box.second != cell.second) {
		moveRobot(rob, box);
		rob = box;
		box.second --;
		ma3x[box.first][box.second] = 1;
	}
	
	ma3x[rob.first][rob.second] = 0;
	printf("DL");
	rob.first --;
	rob.second --;
	
	while(box.first != cell.first - 2) {
		moveRobot(rob, box);
		rob = box;
		box.first ++;
		ma3x[box.first][box.second] = 1;
	}
	
	/// Third box
	go(mp(60, 0));
	rob = mp(60, 0);
	box = mp(60, 1);
	while(box.second != cell.second - 1) {
		moveRobot(rob, box);
		rob = box;
		box.second ++;
		ma3x[box.first][box.second] = 1;
	}
	
	ma3x[rob.first][rob.second] = 0;
	printf("UR");
	rob.first ++;
	rob.second ++;
	
	while(box.first != cell.first) {
		moveRobot(rob, box);
		rob = box;
		box.first --;
		ma3x[box.first][box.second] = 1;
	}
	
	/// Fourth box
	go(mp(60, 61));
	rob = mp(60, 61);
	box = mp(60, 60);
	while(box.second != cell.second + 1) {
		moveRobot(rob, box);
		rob = box;
		box.second --;
		ma3x[box.first][box.second] = 1;
	}
	
	ma3x[rob.first][rob.second] = 0;
	printf("UL");
	rob.first ++;
	rob.second --;
	
	while(box.first != cell.first) {
		moveRobot(rob, box);
		rob = box;
		box.first --;
		ma3x[box.first][box.second] = 1;
	}
	
	printf("\n");
}

int main()
{
	read();
	solve();
	
	return 0;
}
