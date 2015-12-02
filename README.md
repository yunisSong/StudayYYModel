# StudayYYModel

#学习YYModel

##一，调用方法
```
YYGHUser * Model = [YYGHUser yy_modelWithJSON:json];
```

##二，内部实现
```
+ (instancetype)yy_modelWithJSON:(id)json {
    //json 转  NSDictionary
    NSDictionary *dic = [self _yy_dictionaryWithJSON:json];
	//NSDictionary -> model
    return [self yy_modelWithDictionary:dic];
}
```

##三， json 转dic
```

+ (NSDictionary *)_yy_dictionaryWithJSON:(id)json {
	//1,如果 json 为空  return nil
    if (!json || json == (id)kCFNull) return nil;
    
    //2  这里这样写有什么好处吗？
    
    NSDictionary *dic = nil;
    
    NSData *jsonData = nil;
    
    //3，判断json是数据类型
    
    if ([json isKindOfClass:[NSDictionary class]]) {
    
    //如果是NSDictionary类型  把json数据赋值给dic
    
        dic = json;
        
    } else if ([json isKindOfClass:[NSString class]]) {
    
    //如果是NSString类型  把json数据进行NSUTF8StringEncoding编码得到NSData，然后 赋值给jsonData 
        jsonData = [(NSString *)json dataUsingEncoding : NSUTF8StringEncoding];
        
    } else if ([json isKindOfClass:[NSData class]]) {
    
    //如果是NSData类型 直接赋值给jsonData
    
        jsonData = json;
    }
    if (jsonData) {
    
    //如果jsondata数据不为空，调用系统方法NSData -》NSDictionary
        dic = [NSJSONSerialization JSONObjectWithData:jsonData options:kNilOptions error:NULL];
        
        //如果得到的dic 类型不是NSDictionary  dic = nil
        if (![dic isKindOfClass:[NSDictionary class]]) dic = nil;
        
    }
    return dic;
}


```

##四，字典转Model
```

+ (instancetype)yy_modelWithDictionary:(NSDictionary *)dictionary {

	//判断NSDictionary 不为空 
	//这里为什么这么写？有什么优势？求看到的大神指点
	
    if (!dictionary || dictionary == (id)kCFNull) return nil;
    
    //判断dictionary 是否是NSDictionary类型，如果不是NSDictionary类型，return nil
    
    if (![dictionary isKindOfClass:[NSDictionary class]]) return nil;
    
    Class cls = [self class];
    _YYModelMeta *modelMeta = [_YYModelMeta metaWithClass:cls];
    if (modelMeta->_hasCustomClassFromDictionary) {
        cls = [cls modelCustomClassForDictionary:dictionary] ?: cls;
    }
    
    NSObject *one = [cls new];
    if ([one yy_modelSetWithDictionary:dictionary]) return one;
    return nil;
}


```



###1,

```

+ (instancetype)metaWithClass:(Class)cls {
    if (!cls) return nil;
    //这里难道是要做一个缓存区域？
    
    static CFMutableDictionaryRef cache;
    
    static dispatch_once_t onceToken;
    
    static OSSpinLock lock;
    
    dispatch_once(&onceToken, ^{
        cache = CFDictionaryCreateMutable(CFAllocatorGetDefault(), 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
        //谁能告诉我为什么赋这个值  苍天啊大地啊！！！！
        
         /*! @abstract The default value for an <code>OSSpinLock</code>.
         @discussion
         The convention is that unlocked is zero, locked is nonzero.
          #define	OS_SPINLOCK_INIT    0
          
          告诉我们OS_SPINLOCK_INIT 是一个默认值。
          不锁定为0
          锁定为非0；
          
         */
        
        lock = OS_SPINLOCK_INIT;
    });
    //WTF 这个又是什么！！
     /*! @abstract Locks a spinlock
     @discussion
     Although the lock operation spins, it employs various strategies
     to back off if the lock is held, making it immune to most priority-inversion
     livelocks.
     */
    //艹 被吓到了  原来就是个 锁定
    OSSpinLockLock(&lock);
    //我猜这个是根据key等到value 相当于  [NSDictionary objectForKey:@""];
   
    _YYModelMeta *meta = CFDictionaryGetValue(cache, (__bridge const void *)(cls));
    //解锁
    OSSpinLockUnlock(&lock);
    //如果刚才没有得到数据  生成数据并存入cache
    if (!meta) {
        //这里是取得类的@property属性或者全部信息，目前还没有研究到
        meta = [[_YYModelMeta alloc] initWithClass:cls];
        if (meta) {
            //存储值，下次可以直接读取，不需要在生成了。
            OSSpinLockLock(&lock);
            CFDictionarySetValue(cache, (__bridge const void *)(cls), (__bridge const void *)(meta));
            OSSpinLockUnlock(&lock);
        }
    }
    return meta;
}


```

#未完待续























