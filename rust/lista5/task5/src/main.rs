use std::collections::HashSet;

fn main() {}

fn sum_pairs(ints: &[i8], s: i8) -> Option<(i8, i8)> {
    let mut nums: HashSet<i8> = HashSet::new();

    for num in ints {
        //we have to use hashsets, because hashset contains is in O(1) while array.contains is in O(n), which is too slow
        if nums.contains(&(s - num)) {
            return Some((s - num, *num));
        }
        nums.insert(*num);
    }

    None
}

#[test]
fn test() {
    let l1 = [1, 4, 8, 7, 3, 15];
    assert_eq!(sum_pairs(&l1, 8), Some((1, 7)));
}

#[test]
fn test2() {
    let l2: [i8; 6] = [1, -2, 3, 0, -6, 1];
    assert_eq!(sum_pairs(&l2, -6), Some((0, -6)));
}

#[test]
fn test3() {
    let l3 = [20, -13, 40];
    assert_eq!(sum_pairs(&l3, -7), None);
}

#[test]
fn test4() {
    let l4 = [1, 2, 3, 4, 1, 0];
    assert_eq!(sum_pairs(&l4, 2), Some((1, 1)));
}

#[test]
fn test5() {
    let l5: [i8; 6] = [10, 5, 2, 3, 7, 5];
    assert_eq!(sum_pairs(&l5, 10), Some((3, 7)));
}
