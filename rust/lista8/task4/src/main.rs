fn main() {
    println!("Hello, world!");
}

fn rules(n: i32, person: i32) -> Vec<i32> {
    let mut john_vec = vec![0];
    let mut ann_vec = vec![1];

    for x in 1..n {
        let ann_t = john_vec[(x - 1) as usize] as usize;
        john_vec.push(x - ann_vec[ann_t]);
        let john_t = ann_vec[(x - 1) as usize] as usize;
        ann_vec.push(x - john_vec[john_t]);
    }

    if person == 0 {
        john_vec
    } else {
        ann_vec
    }
}

fn john(n: i32) -> Vec<i32> {
    rules(n, 0)
}

fn ann(n: i32) -> Vec<i32> {
    rules(n, 1)
}

fn sum_john(n: i32) -> i32 {
    john(n).into_iter().sum()
}

fn sum_ann(n: i32) -> i32 {
    ann(n).into_iter().sum()
}

#[test]
fn test_john() {
    assert_eq!(john(11), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6]);
    assert_eq!(john(14), vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 7, 8]);
}
#[test]
fn test_ann() {
    assert_eq!(ann(6), vec![1, 1, 2, 2, 3, 3]);
    assert_eq!(ann(15), vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9]);
}
#[test]
fn test_sum_john() {
    assert_eq!(sum_john(75), 1720);
    assert_eq!(sum_john(78), 1861);
}
#[test]
fn test_sum_ann() {
    assert_eq!(sum_ann(115), 4070);
    assert_eq!(sum_ann(150), 6930);
}
