package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
)

func readfile(path string) []string {
	f, err := os.Open(path)
	if err != nil {
		panic(err)
	}
	defer f.Close()
	lines := make([]string, 0, 200)
	sc := bufio.NewScanner(f)
	for sc.Scan() {
		lines = append(lines, sc.Text())
	}
	return lines
}

func checkreg(lines []string) []int {
	pattern := `\(\d+\)`
	re := regexp.MustCompile(pattern)
	result := make([]int, len(lines))
	for i := 0; i < len(lines); i++ {
		num := re.FindString(lines[i])
		result[i], _ = strconv.Atoi(num[1:(len(num) - 1)])
	}
	return result
}

func count(start int, end int, m []int) int {
	acc := 0
	for i := start - 1; i < end; i++ {
		acc += m[i]
	}
	return acc
}
func count2(n int, m []int) int {
	acc := 0
	result := 0
	for i := 0; acc < n; i++ {
		acc += m[i]
		result++
	}
	return result
}

func main() {
	lines := readfile("file.txt")
	res := checkreg(lines)
	fmt.Println("Points counter:", count(1, 90, res))
	fmt.Println("170 points:", count2(170, res), "tasks")
}
