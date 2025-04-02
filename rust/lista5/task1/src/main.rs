fn main() {}

fn count_odd_pentafib(n: u16) -> u16 {
    if n == 0 {
        return 0;
    } else if n <= 4 {
        return 1;
    }

    let mut seq = vec![0, 1, 1, 2, 4];
    let mut odd = 1;
    for i in 5..=n {
        let val: i32 = seq.iter().sum();
        if val % 2 == 1 {
            odd += 1;
        }
        let index = (i % 5) as usize;
        seq[index] = val % 2;
    }

    odd
}

#[test]
fn test1() {
    assert_eq!(count_odd_pentafib(5), 1);
}
#[test]
fn test2() {
    assert_eq!(count_odd_pentafib(68), 23);
}
#[test]
fn test3() {
    assert_eq!(count_odd_pentafib(45), 15);
}
#[test]
fn test4() {
    assert_eq!(count_odd_pentafib(0), 0);
}
#[test]
fn test5() {
    assert_eq!(count_odd_pentafib(15), 5);
}
