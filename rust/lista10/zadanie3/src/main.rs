fn main() {
    println!("Hello, world!");
}

fn comp(a: Vec<i64>, b: Vec<i64>) -> bool {
    if a.len() != b.len() {
        return false;
    }
    let mut res = b;
    for el in &a {
        if let Some(index) = res.iter().position(|&x| x == el * el) {
            res.remove(index);
        }
    }
    res.is_empty()
}

fn testing(a: Vec<i64>, b: Vec<i64>, exp: bool) -> () {
    assert_eq!(comp(a, b), exp)
}

#[test]
fn tests_comp1() {
    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![
        11 * 11,
        121 * 121,
        144 * 144,
        19 * 19,
        161 * 161,
        19 * 19,
        144 * 144,
        19 * 19,
    ];
    testing(a1, a2, true);
}

#[test]
fn tests_comp2() {
    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![
        11 * 21,
        121 * 121,
        144 * 144,
        19 * 19,
        161 * 161,
        19 * 19,
        144 * 144,
        19 * 19,
    ];
    testing(a1, a2, false);
}

#[test]
fn tests_comp3() {
    let a1 = vec![2, 4, 4, 6];
    let a2 = vec![4, 36, 16, 16];
    testing(a1, a2, true);
}

#[test]
fn tests_comp4() {
    let a1 = vec![2, 4, 4, 6, 5];
    let a2 = vec![4, 36, 16, 16];
    testing(a1, a2, false);
}

#[test]
fn tests_comp5() {
    let a1 = vec![2, 4, 4, 6, 5];
    let a2 = vec![4, 36, 16, 16, 25, 4];
    testing(a1, a2, false);
}
