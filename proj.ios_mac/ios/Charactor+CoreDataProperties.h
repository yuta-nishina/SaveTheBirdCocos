//
//  Charactor+CoreDataProperties.h
//  SaveTheBird
//
//  Created by ATGS_Mac on 2016/05/23.
//
//
//  Choose "Create NSManagedObject Subclass…" from the Core Data editor menu
//  to delete and recreate this implementation file for your updated model.
//

#import "Charactor.h"

NS_ASSUME_NONNULL_BEGIN

@interface Charactor (CoreDataProperties)

@property (nullable, nonatomic, retain) NSString *detail;
@property (nullable, nonatomic, retain) NSString *image_stand;
@property (nullable, nonatomic, retain) NSString *name;
@property (nullable, nonatomic, retain) NSNumber *no;

@end

NS_ASSUME_NONNULL_END
