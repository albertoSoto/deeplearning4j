/*-
 *  * Copyright 2016 Skymind, Inc.
 *  *
 *  *    Licensed under the Apache License, Version 2.0 (the "License");
 *  *    you may not use this file except in compliance with the License.
 *  *    You may obtain a copy of the License at
 *  *
 *  *        http://www.apache.org/licenses/LICENSE-2.0
 *  *
 *  *    Unless required by applicable law or agreed to in writing, software
 *  *    distributed under the License is distributed on an "AS IS" BASIS,
 *  *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  *    See the License for the specific language governing permissions and
 *  *    limitations under the License.
 */

package org.datavec.spark.transform.misc;

import lombok.AllArgsConstructor;
import org.apache.spark.api.java.function.Function;
import org.datavec.api.records.reader.RecordReader;
import org.datavec.api.split.StringSplit;
import org.datavec.api.writable.Writable;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

/**
 * Convert a String to a List<Writable> using a DataVec record reader
 *
 */
@AllArgsConstructor
public class StringToWritablesFunction implements Function<String, List<Writable>> {

    private RecordReader recordReader;

    @Override
    public List<Writable> call(String s) throws Exception {
        recordReader.initialize(new StringSplit(s));
        Collection<Writable> next = recordReader.next();
        if (next instanceof List)
            return (List<Writable>) next;
        return new ArrayList<>(next);
    }
}
