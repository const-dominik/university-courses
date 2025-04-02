fn main() {}

fn expanded_form(mut n: u64) -> String {
    let mut result: Vec<u64> = vec![];
    for i in 0..(n.to_string().len() as u32) {
        let num = n % 10;
        if num != 0 {
            let val = num * u64::pow(10, i);
            result.push(val);
            n -= num;
        }
        n /= 10;
    }

    result
        .into_iter()
        .rev()
        .map(|num| num.to_string())
        .collect::<Vec<String>>()
        .join(" + ")
}

#[test]
fn test() {
    assert_eq!(expanded_form(70304), "70000 + 300 + 4");
}
#[test]
fn test2() {
    assert_eq!(expanded_form(352), "300 + 50 + 2");
}
#[test]
fn test3() {
    assert_eq!(expanded_form(1), "1");
}
#[test]
fn test4() {
    assert_eq!(expanded_form(20000), "20000");
}
#[test]
fn test5() {
    assert_eq!(expanded_form(12345), "10000 + 2000 + 300 + 40 + 5");
}
