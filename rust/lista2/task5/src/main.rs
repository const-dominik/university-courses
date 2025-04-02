fn main() {}

fn gimme_the_letters(sp: &str) -> String {
    let first_letter = sp.chars().nth(0).unwrap();
    let second_letter = sp.chars().nth(2).unwrap();

    (first_letter..=second_letter).collect()
}

#[test]
fn fixed_tests() {
    assert_eq!(gimme_the_letters("a-z"), "abcdefghijklmnopqrstuvwxyz");
}

#[test]
fn test2() {
    assert_eq!(gimme_the_letters("a-b"), "ab");
}

#[test]
fn test3() {
    assert_eq!(gimme_the_letters("A-A"), "A");
}

#[test]
fn test4() {
    assert_eq!(gimme_the_letters("g-i"), "ghi");
}

#[test]
fn test5() {
    assert_eq!(gimme_the_letters("F-O"), "FGHIJKLMNO");
}
