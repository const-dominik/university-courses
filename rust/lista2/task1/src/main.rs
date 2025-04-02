fn main() {}

fn count_vowels(string: &str) -> usize {
    let vowels = "aeiou";

    string.chars().filter(|&c| vowels.contains(c)).count()
}

#[test]
fn test_count_vowels() {
    assert_eq!(count_vowels("abcdef"), 2);
}

#[test]
fn test_count_vowels2() {
    assert_eq!(count_vowels(""), 0);
}

#[test]
fn test_count_vowels3() {
    assert_eq!(count_vowels("aeiou"), 5);
}

#[test]
fn test_count_vowels4() {
    assert_eq!(count_vowels("aeiouy"), 5);
}

#[test]
fn test_count_vowels5() {
    assert_eq!(count_vowels("dlksgjlkagkdsl"), 1);
}
