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
    if (used[x]) {
        return x;
    } else {
        parent[x] = alive(parent[x])
        return parent[x]
    }
}
func initAll(n int) {
    v = make([][]int, n, n);
    depth = make([]int, n, n)
    parent = make([]int, n, n)
    used = make([]bool, n, n)
    up = make([][]int, n, n)
 
    l = 1;
    for math.Pow(2, float64(l)) <= float64(n) {
        l++;
    }
    for i := 1; i < n; i++ {
        up[i] = make([]int, l+1, l+1)
        used[i] = true;
    }
    dsuInit(n)
}
 
var dsu []int
 
func dsuInit(n int) {
    dsu = make([]int, n, n)
    for i, _ := range dsu {
        dsu[i] = i;
    }
}
func dsuFind(n int)int {
    if(n == dsu[n]){
        return n
    } else {
        dsu[n] = dsuFind(dsu[n])
        return dsu[n]
    }
}
func dsuUnion(a int, b int) {
    a = dsuFind(a)
    b = dsuFind(b)
    dsu[b] = a;
}
 
func main() {
    fi, _ := os.Open("lca3.in")
    fo, _ := os.Create("lca3.out")
    scanner := bufio.NewScanner(fi)
    scanner.Split(bufio.ScanWords)
    writer := bufio.NewWriter(fo)
    defer fi.Close()
    defer fo.Close()
    defer writer.Flush()
 
    scanner.Scan()
    n, _ := strconv.Atoi(scanner.Text())
    initAll(n + 1)
 
    for i := 1;i <= n;i++ {
        scanner.Scan()
        a, _ := strconv.Atoi(scanner.Text())
        if(a != 0) {
            v[a] = append(v[a], i)
            used[i] = false
            dsuUnion(a, i)
        }
    }
    for i:=1;i<=n ;i++  {
        if(used[i]){
            dfs(i, i, 0)
        }
    }
    //foo(0, 0, 0)
    scanner.Scan()
    m, _ := strconv.Atoi(scanner.Text())
    ans := 0;
    for i := 0; i < m; i++ {
        scanner.Scan()
        s := scanner.Text();
        scanner.Scan()
        a, _ := strconv.Atoi(scanner.Text());
        scanner.Scan()
        b, _ := strconv.Atoi(scanner.Text());
        u := (a - 1 + ans)%n + 1
        q := (b - 1 + ans)%n + 1
        if (s == "1") {
            u = dsuFind(u)
            dsuUnion(q, u)
            v[q] = append(v[q], u)
            dfs(u,q,depth[q] + 1)
        } else if (s == "0") {
            if(dsuFind(u) != dsuFind(q)){
                ans = 0
            } else {
                ans = (lca(u, q))
            }
            writer.WriteString(strconv.Itoa(ans))
            writer.WriteByte('\n')
        }
    }
}