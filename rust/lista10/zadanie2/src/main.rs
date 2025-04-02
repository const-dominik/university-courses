fn main() {}

fn dig_pow(n: i64, p: i32) -> i64 {
    let res: i128 = n
        .to_string()
        .chars()
        .enumerate()
        .map(|(index, num)| (num.to_digit(10).unwrap() as i128).pow((p + index as i32) as u32))
        .sum();
    if res % n as i128 == 0 {
        (res / n as i128) as i64
    } else {
        -1
    }
}

fn dotest(n: i64, p: i32, exp: i64) -> () {
    println!(" n: {:?};", n);
    println!("p: {:?};", p);
    let ans = dig_pow(n, p);
    println!(" actual:\n{:?};", ans);
    println!("expect:\n{:?};", exp);
    println!(" {};", ans == exp);
    assert_eq!(ans, exp);
    println!("{};", "-");
}

#[test]
fn basic_tests1() {
    dotest(89, 1, 1);
}

#[test]
fn basic_tests2() {
    dotest(92, 1, -1);
}

#[test]
fn basic_tests3() {
    dotest(46288, 3, 51);
}

#[test]
fn basic_tests4() {
    dotest(12, 1, -1);
}

#[test]
fn basic_tests5() {
    dotest(111, 21, -1);
}
