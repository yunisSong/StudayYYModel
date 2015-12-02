//
//  ViewController.m
//  StudayYYModel
//
//  Created by 宋尚永 on 15/12/2.
//  Copyright © 2015年 yunis. All rights reserved.
//

#import "ViewController.h"
#import "YYGHUser.h"
@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    NSString *path = [[NSBundle mainBundle] pathForResource:@"user" ofType:@"json"];
    NSData *data = [NSData dataWithContentsOfFile:path];
    NSDictionary *json = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];
    // Do any additional setup after loading the view, typically from a nib.
    
    
    YYGHUser * Model = [YYGHUser yy_modelWithJSON:json];
    NSLog(@"Model == %@",Model);
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
