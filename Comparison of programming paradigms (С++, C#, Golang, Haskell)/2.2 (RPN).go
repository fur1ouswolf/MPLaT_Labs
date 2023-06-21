package main

import (
	"fmt"
	"strconv"
	"strings"
	"time"
)

func evalRPN(tokens []string) int {
	stack := []int{}
	operators := map[string]func(int, int) int{
		"+": func(a, b int) int { return a + b },
		"-": func(a, b int) int { return a - b },
		"*": func(a, b int) int { return a * b },
		"/": func(a, b int) int { return a / b },
	}
	for _, token := range tokens {
		if calculate, exist := operators[token]; exist {
			a, b := stack[len(stack)-2], stack[len(stack)-1]
			stack = append(stack[:len(stack)-2], calculate(a, b))
		} else {
			num, _ := strconv.Atoi(token)
			stack = append(stack, num)
		}
	}
	return stack[0]
}

// Test time of execution
func timeTrack(start time.Time) {
	elapsed := time.Since(start)
	fmt.Printf("Time: %s\n", elapsed)
}

func test(f func([]string) int, tokens []string, n int) {
	defer timeTrack(time.Now())
	for i := 0; i < n; i++ {
		f(tokens)
	}
	return
}

func main() {
	var expression string = "10 6 9 3 + -11 * / * 17 + 5 +"
	tokens := strings.Split(expression, " ")
	fmt.Printf("Result: %d\n", evalRPN(tokens))
	test(evalRPN, tokens, 1000000)
}
