/*
Codeforces Round 587 - White Sheet - https://codeforces.com/contest/1216/problem/C

Geometry - Checking if two black rectangles completely cover a third white one.

Solution: 1. Find the two intersections bw1, bw2 of the black rectangles with the white one.
          2. Find the intersection inter of the bw1, bw2
          3. Then the white rectangle is covered if:
             area(bw1) + area(bw2) - area(inter) >= area(white)

Watch out for:  - numbers are too large for int, use long.
                - To find the intersection of two rectangles:
                    BottomLeftx = Take Max(r1.bottomLeft.x, r2.bottomLeft.x)
                    BottomLefty = Take Max(r1.bottomLeft.y, r2.bottomLeft.y)
                    TopRightx   = Take Min(r1.topRight.x, r2.topRight.y)

                - because if you have the bottomLeft and the topRight coordinate
                 topRight.x > bottomLeft.x && topRight.y > bottomLeft.y
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public final class WhiteSheet {
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }

        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }

    static class Point {
        long x;
        long y;

        Point(long x, long y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public String toString() {
            return "(" + this.x + ", " + this.y + ")";
        }
    }

    static class Rectangle {

        Point bottomLeft;
        Point topRight;

        Rectangle(Point bl, Point tr) {
            bottomLeft = bl;
            topRight = tr;
        }

        @Override
        public String toString() {
            return "Bottom Left: " + bottomLeft.toString() + '\n' + "Top Right: " + topRight.toString();

        }
    }

    public static Rectangle intersection(Rectangle r1, Rectangle r2) {
        Point bottomLeft = new Point(Math.max(r1.bottomLeft.x, r2.bottomLeft.x),
                Math.max(r1.bottomLeft.y, r2.bottomLeft.y));
        Point topRight = new Point(Math.min(r1.topRight.x, r2.topRight.x), Math.min(r1.topRight.y, r2.topRight.y));
        if (bottomLeft.x > topRight.x || bottomLeft.y > topRight.y) {
            return new Rectangle(new Point(0, 0), new Point(0, 0));
        }
        return new Rectangle(bottomLeft, topRight);
    }

    public static long area(Rectangle r) {
        return (r.topRight.x - r.bottomLeft.x) * (r.topRight.y - r.bottomLeft.y);
    }

    public static void main(String[] args) {
        FastReader fs = new FastReader();
        Rectangle white = new Rectangle(new Point(fs.nextLong(), fs.nextLong()),
                new Point(fs.nextLong(), fs.nextLong()));
        Rectangle b1 = new Rectangle(new Point(fs.nextLong(), fs.nextLong()), new Point(fs.nextLong(), fs.nextLong()));
        Rectangle b2 = new Rectangle(new Point(fs.nextLong(), fs.nextLong()), new Point(fs.nextLong(), fs.nextLong()));

        Rectangle bw1 = intersection(white, b1);
        Rectangle bw2 = intersection(white, b2);
        Rectangle bb = intersection(bw1, bw2);

        if (area(bw1) + area(bw2) - area(bb) >= area(white)) {
            System.out.println("NO");
        } else {
            System.out.println("YES");
        }
    }
}