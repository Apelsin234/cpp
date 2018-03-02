package main
 
import (
    "math"
 
    "os"
    "bufio"
    "strconv"
)
 
func check(err error) {
    if err == nil {
        panic("hyianik")
    }
}
 
var v [][]int
var depth []int
var parent []int
var used []bool
var up [][]int
var l int
 
func dfs(u int, p int, d int) {
    depth[u] = d
    up[u][0] = p
    for i := 1; i <= l; i++ {
        up[u][i] = up[up[u][i-1]][i-1];
    }
    for i := 0; i < len(v[u]); i++ {
        if v[u][i] != p {
            dfs(v[u][i], u, d+1)
        }
    }
}
 
func foo(u int, p int, d int) {
    depth[u] = d
    parent[u] = p
    up[u][0] = p
    for i := 1; i <= l; i++ {
        up[u][i] = up[up[u][i-1]][i-1];
    }
}
 
func lca(a int, b int) int {
    if depth[a] > depth[b] {
        a, b = b, a
    }
    for i := l; i >= 0; i-- {
        if float64(depth[b]-depth[a]) >= math.Pow(2, float64(i)) {
            b = up[b][i]
        }
    }
    if a == b {
        return a;
    }
 
    for i := l; i >= 0; i-- {
        if up[a][i] != up[b][i] {
            b = up[b][i]
            a = up[a][i]
        }
    }
 
    return up[a][0]
 
}
 
func alive(x int) int {
    if(used[x]){
        return x;
    } else {
         parent[x] = alive(parent[x])
         return parent[x]
    }
}
 
func main() {
    fi, _ := os.Open("carno.in")
    fo, _ := os.Create("carno.out")
    scanner := bufio.NewScanner(fi)
    scanner.Split(bufio.ScanWords)
    writer := bufio.NewWriter(fo)
    defer fi.Close()
    defer fo.Close()
    defer writer.Flush()
 
    scanner.Scan()
    n, _ := strconv.Atoi(scanner.Text())
 
    v = make([][]int, n, n);
    depth = make([]int, n, n)
    parent = make([]int, n, n)
    used = make([]bool, n, n)
    up = make([][]int, n, n)
    l = 1;
    for math.Pow(2, float64(l)) <= float64(n) {
        l++;
    }
    for i := 0; i < n; i++ {
        up[i] = make([]int, l+1, l+1)
        used[i] = true;
    }
    //dfs(0, 0, 0)
    foo(0, 0, 0)
    //scanner.Scan()
    //m, _ := strconv.Atoi(scanner.Text())
    k := 1;
    for i := 0; i < n; i++ {
        scanner.Scan()
        s := scanner.Text();
        scanner.Scan()
        a, _ := strconv.Atoi(scanner.Text());
        if (s == "+") {
            v[a-1] = append(v[a-1], k)
            foo(k, a-1, depth[a-1]+1);
            k++
        } else if (s == "?") {
            scanner.Scan()
            b, _ := strconv.Atoi(scanner.Text());
            writer.WriteString(strconv.Itoa(alive((lca(a-1, b-1))) + 1))
            writer.WriteByte('\n')
        } else {
            used[a-1] = false
        }
    }
}