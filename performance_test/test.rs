use std::time::Instant;

// 递归计算斐波那契数
fn fibonacci_recursive(n: i32) -> i32 {
    if n <= 1 {
        n
    } else {
        fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2)
    }
}

fn main() {
    let n = 40; // 递归深度，避免太大的n值导致栈溢出
    let start = Instant::now();
    let result = fibonacci_recursive(n);
    let duration = start.elapsed();
    println!(
        "Recursive Rust: Fibonacci({}) = {}, Time = {:.9} seconds",
        n, result, duration.as_secs_f64()
    );
}