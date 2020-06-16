package main // package definition

import "fmt" // format

func substr(str, sub string) bool {
	for i := 0; i < len(str); i++ {
		if str[i] == sub[0] {
			for j := 0; i+j < len(str) && j < len(sub) && str[i] == sub[j]; j++ {
				if len(sub) == (j + 1) {
					return true
				}
				i++
			}
		}
	}
	return false
}

func min(x []int) int {
	min := x[0]
	for _, value := range x {
		if value < min {
			min = value
		}
	}
	return min
}

func gcd(a, b int) int {
	if b == 0 {
		return a
	}
	return gcd(b, a%b)
}

func main() {
	fmt.Println(gcd(12, 30))                  // 6
	fmt.Println(min([]int{1, 2, 3, 0, 4, 5})) // 0
	fmt.Println(substr("hello", "llon"))      // fasle
}
