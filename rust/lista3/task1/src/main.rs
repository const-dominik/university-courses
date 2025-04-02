fn main() {
    println!("{}", row_sum_odd_numbers(5))
}

fn row_sum_odd_numbers(n: i64) -> i64 {
    // (n * (n - 1) + 1) * n + n * (n - 1)
    //  first element n times + 2*sum of arithmetic sequence from 1 to n-1
    n * n * n
}

#[test]
fn test_1() {
    assert_eq!(row_sum_odd_numbers(1), 1);
}

#[test]
fn test_2() {
    assert_eq!(row_sum_odd_numbers(2), 8);
}

#[test]
fn test_3() {
    assert_eq!(row_sum_odd_numbers(3), 27);
}

#[test]
fn test_4() {
    assert_eq!(row_sum_odd_numbers(4), 64);
}

#[test]
fn test_5() {
    assert_eq!(row_sum_odd_numbers(5), 125);
}
