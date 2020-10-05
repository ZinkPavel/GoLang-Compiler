package main // package definition

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func main() {
	var x int = 40
	var y int = 30

	max(x, y)
}
