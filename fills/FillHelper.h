#define FLOOD_FILL 0
#define SCAN_LINE 1
#define DEFAULT_FILL FLOOD_FILL

class FillHelper {
protected:
    void doFloodFill(ShadowBuffer& sb, vector<Point> points);
    //void do....

public:
    void doFill(int type, ShadowBuffer& sb, vector<Point> points);
    
};