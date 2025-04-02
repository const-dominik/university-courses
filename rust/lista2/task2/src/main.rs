fn main() {}

fn longest(a1: &str, a2: &str) -> String {
    let concatenated = a1.to_string() + a2;
    let mut distinct: Vec<char> = concatenated.chars().collect();
    distinct.sort();
    distinct.dedup(); // dedup removes only adjacent duplicates, wouldn't work without sorting first

    distinct.into_iter().collect()
}

#[test]
fn test_longest() {
    assert_eq!(longest("abc", "def"), "abcdef");
}

#[test]
fn test2() {
    assert_eq!(longest("abc", "abc"), "abc");
}

#[test]
fn test3() {
    assert_eq!(longest("aretheyhere", "yestheyarehere"), "aehrsty");
}

#[test]
fn test4() {
    assert_eq!(
        longest("loopingisfunbutdangerous", "lessdangerousthancoding"),
        "abcdefghilnoprstu"
    );
}

#[test]
fn test5() {
    assert_eq!(
        longest("xyaabbbccccdefww", "xxxxyyyyabklmopq"),
        "abcdefklmopqwxy"
    );
}
